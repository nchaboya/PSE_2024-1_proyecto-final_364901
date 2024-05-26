# Proyecto Final | Control de Apertura de Persianas Programable

## Objetivo

Aplicar los conocimientos, técnicas y herramientas aprendidos y utilizados a lo largo del curso de Programación de Sistemas Empotrados para crear un dispositivo de fácil uso que permita programar la apertura y cierre de una persiana, empleando un motor de pasos.

## Introducción

La automatización del hogar es una tendencia en crecimiento debido a los múltiples beneficios que ofrece, como la comodidad, la eficiencia energética y la seguridad. El presente proyecto tiene como principal objetivo implementar un sistema empotrado cuyo propósito sea automatizar algún elemento de un hogar, en este caso particular una persiana vertical, ofreciendo una alternativa de bajo costo relativo al de otros sistemas de automatización o de Internet de las Cosas que se encuentran actualmente en el mercado. En última instancia, el sistema ofrece una solución de comodidad al permitir que el usuario programe la hora de apertura y cierre de persianas, y que se controla mediante un reloj de tiempo real integrado al circuito.

## Materiales

### Software

- Arduino IDE
- Bibliotecas especializadas para el hardware y actuadores utilizados en la presente práctica:
  - Wire.h
  - DS321
  - Adafruit
  - Stepper.h

### Hardware

- Tarjeta ELEGOO UNO R3: plataforma de desarrollo basada en la Arduino Uno
- Reloj de tiempo real AT24C32
- Controlador-puente H L298 para motor de pasos
- Pantalla OLED de 128×32 píxeles
- Adaptador-fuente de 7.5 V y 2000 mA
- Cables jumper
- Jumpers hembra-macho
- Switches de Push
- Adaptador DC
- Protoboard
- Resistencias

### Actuadores

- Motor de pasos NEMA 17

## Contenido del Repositorio

En este repositorio se encuentra:

- **/codigo:** Contiene el código principal del programa y el programa para sincronizar el RTC.
- **/documentacion:** Incluye el documento del reporte, el de la presentación del proyecto y en el subdirectorio **/figuras**, las figuras usadas en el reporte.

Este proyecto está diseñado para facilitar la implementación de un sistema de apertura y cierre de persianas programable utilizando una tarjeta Arduino y componentes de bajo costo, ofreciendo una solución accesible y eficiente para la automatización del hogar.

## Referencias
1. HiBit (2020). *How to use the L298N motor driver module*. Recuperado de: [https://www.hibit.dev/posts/89/how-to-use-the-l298n-motor-driver-module]
2. Mallari, J. (2022). *HOW TO USE A REAL-TIME CLOCK MODULE WITH THE ARDUINO*. Recuperado de: [https://www.circuitbasics.com/how-to-use-a-real-time-clock-module-with-the-arduino/]
3. Components 101. *Nema 17 Stepper Motor*. Recuperado de: [https://components101.com/motors/nema17-stepper-motor]
4. Zmabetti, N., Soderby, K., Hylén, J. (2024). *Inter-Integrated Circuit (I2C) Protocol*. Recuperado de: [https://docs.arduino.cc/learn/communication/wire/]