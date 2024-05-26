#include <Wire.h>//https://www.arduino.cc/en/reference/wire
#include <DS3231.h>//https://github.com/NorthernWidget/DS3231
#include <Adafruit_GFX.h> 
#include <Adafruit_SSD1306.h>
#include <Stepper.h>
#define OLED_RESET 13 

Adafruit_SSD1306 display(OLED_RESET);

bool Century = false,  h12, PM, closed = false, open = true;
int openH = 6,  closeH = 12, openM = 0, closeM = 4;
const int stepsPerRevolution = 200;

//Objects
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
 	//Serial.println(readRTC());
  displayT();
  readInputs();
  stepperCheck(); 
  delay(100);  
}

String readRTC( ) {
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

void displayT() { 
  display.clearDisplay(); 
  display.setTextSize(1); // 1 a 8
  display.setTextColor(WHITE); 
  display.setCursor(0,0); 
  display.println(readRTC()); 

  display.setCursor(0,12); 
  display.println(readCloseT() +  "    | Cerrar");
  display.setTextSize(1); // 1 a 8
  display.setTextColor(WHITE); 
  display.setCursor(0,24); 
  display.println(readOpenT() + "    | Abrir");
  display.display();
}

void readInputs(){
  if (digitalRead(2) == HIGH){
   	//Serial.println("High on 2");
    closeM = (closeM + 1) % 6;
    //Serial.println(closeM);
    if (closeM == 0)
      closeH = (closeH + 1) % 24;
  }
  if (digitalRead(3) == HIGH){
   	//Serial.println("High on 3");
    openM = (openM + 1) % 6;
    //Serial.println(openM);
    if (openM == 0)
      openH = (openH + 1) % 24;
  }
  
}

String readOpenT( ) { 
  String s = "";
  if (openH < 10) s += "0";
  s += String(openH) + ":" + String(openM) + "0";
  return s;
}

String readCloseT( ) { 
  String s = "";
  if (closeH < 10) s += "0";
  s += String(closeH) + ":" + String(closeM) + "0";
  return s;
}

void stepperCheck(){
  if (Clock.getHour(h12, PM) == closeH && Clock.getMinute() == 10*closeM && closed == false){
    closed = true;
    open = false;
    stepper.step(2*stepsPerRevolution);
  }
  if (Clock.getHour(h12, PM) == openH && Clock.getMinute() == 10*openM && open == false){
    closed = false;
    open = true;
    stepper.step(-2*stepsPerRevolution);
  }
}

void setupClosureStatus(){
  if (Clock.getHour(h12, PM) >= openH && Clock.getHour(h12, PM) < closeH){
    closed = false;
    open = true;
  }
  else{
    closed = true;
    open = false;
  }
}
