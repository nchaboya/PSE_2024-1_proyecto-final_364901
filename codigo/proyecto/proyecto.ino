#include <Wire.h> // Biblioteca para comunicación I2C
#include <DS3231.h> // Biblioteca para el reloj de tiempo real DS3231
#include <Adafruit_GFX.h> // Biblioteca para gráficos
#include <Adafruit_SSD1306.h> // Biblioteca para pantallas OLED SSD1306
#include <Stepper.h> // Biblioteca para control de motores de pasos
#define OLED_RESET 13

Adafruit_SSD1306 display(OLED_RESET); 

// Variables globales
bool Century = false, h12, PM, closed = false, open = true;
int openH = 6, closeH = 12, openM = 0, closeM = 4; // Horas y minutos de apertura y cierre
const int stepsPerRevolution = 200; // Número de pasos por revolución del motor de pasos

// Objetos
DS3231 Clock; 
Stepper stepper(stepsPerRevolution, 8, 9, 10, 11); 

void setup() {
    Serial.begin(9600); 
    pinMode(2, INPUT); 
    pinMode(3, INPUT); 
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
    stepper.setSpeed(60); 
    //setupClosureStatus();

    Serial.println(F("Initialize System")); 
    Wire.begin(); 
}

void loop() {
    displayT(); // Muestra la hora y el estado en la pantalla OLED
    readInputs(); // Lee las entradas de los botones
    stepperCheck(); // Verifica si debe mover la persiana
    delay(100); 
}

// Función para leer la hora del reloj DS3231 y formatearla como una cadena
String readRTC() {
    String s = "";

    int hour = Clock.getHour(h12, PM);
    if (hour < 10) s += "0";
    s += String(hour, DEC) + ":";

    int min = Clock.getMinute();
    if (min < 10) s += "0";
    s += String(min, DEC) + ":";

    int sec = Clock.getSecond();
    if (sec < 10) s += "0";
    s += String(sec, DEC) + " | ";

    int date = Clock.getDate();
    if (date < 10) s += "0";
    s += String(date, DEC) + "/";

    int month = Clock.getMonth(Century);
    if (month < 10) s += "0";
    s += String(month, DEC) + "/";

    s += "20" + String(Clock.getYear(), DEC);

    return s;
}

// Función para mostrar la hora y el estado de apertura/cierre en la pantalla OLED
void displayT() {
    display.clearDisplay(); 
    display.setTextSize(1); 
    display.setTextColor(WHITE); 
    display.setCursor(0, 0); 
    display.println(readRTC()); 

    display.setCursor(0, 12); 
    display.println(readCloseT() + "    | Cerrar"); // Muestra la hora de cierre
    display.setTextSize(1); 
    display.setTextColor(WHITE); 
    display.setCursor(0, 24); 
    display.println(readOpenT() + "    | Abrir"); // Muestra la hora de apertura
    display.display(); // Actualiza la pantalla
}

// Función para leer las entradas de los botones y ajustar las horas de apertura y cierre
void readInputs() {
    if (digitalRead(2) == HIGH) { // Si el botón en el pin 2 está presionado
        closeM = (closeM + 1) % 6; // Incrementa los minutos de cierre
        if (closeM == 0) // Si los minutos son 0, incrementa la hora de cierre
            closeH = (closeH + 1) % 24;
    }
    if (digitalRead(3) == HIGH) { // Si el botón en el pin 3 está presionado
        openM = (openM + 1) % 6; // Incrementa los minutos de apertura
        if (openM == 0) // Si los minutos son 0, incrementa la hora de apertura
            openH = (openH + 1) % 24;
    }
}

// Función para obtener la hora de apertura como una cadena
String readOpenT() {
    String s = "";
    if (openH < 10) s += "0";
    s += String(openH) + ":" + String(openM) + "0";
    return s;
}

// Función para obtener la hora de cierre como una cadena
String readCloseT() {
    String s = "";
    if (closeH < 10) s += "0";
    s += String(closeH) + ":" + String(closeM) + "0";
    return s;
}

// Función para verificar si es hora de abrir o cerrar la persiana y mover el motor
void stepperCheck() {
    if (Clock.getHour(h12, PM) == closeH && Clock.getMinute() == 10 * closeM && closed == false) {
        closed = true;
        open = false;
        stepper.step(2 * stepsPerRevolution); // Mueve el motor para cerrar la persiana
    }
    if (Clock.getHour(h12, PM) == openH && Clock.getMinute() == 10 * openM && open == false) {
        closed = false;
        open = true;
        stepper.step(-2 * stepsPerRevolution); // Mueve el motor para abrir la persiana (en sentido contrario)
    }
}

// Función para configurar el estado inicial de la persiana según la hora actual
void setupClosureStatus() {
    if (Clock.getHour(h12, PM) >= openH && Clock.getHour(h12, PM) < closeH) {
        closed = false;
        open = true;
    } else {
        closed = true;
        open = false;
    }
}
