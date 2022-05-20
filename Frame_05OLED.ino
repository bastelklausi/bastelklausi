/*
 * Mini Controller für Fischertechnik
 * Basiert auf Arduino Nano
 *   steuert 2 Motoren über 293D IC
 *   steuert 3 LED über Transistor
 *   erkennt 4 Eingänge
 *   wertet 1 Poti an A7 aus
 *   unterstützt I2C Display SSD1306
 *   
 * Version 0.5 vom 20.5.2022
 */

// OLED Support
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Motorfunktionen
#define MotorA   1
#define MotorB   2
#define FORWARD  1
#define BACKWARD 2
#define STOP     3

// Motor A Pins
int enA = 9;
int in1 = 8;
int in2 = 7;
// Motor B Pins
int enB = 3;
int in3 = 2;
int in4 = 4;

// LED Funktionen
#define Led1 10
#define Led2 11
#define Led3 6
#define LedIntern 13

// Eingangsfunktionen
// Analogeingänge mit 47k gegen 5V geschaltet
// Taster schaltet GND gegen Eingang (Taster gedrückt = 1, sonst 0)
// Fototransistor schaltet Pluspol gegen Eingang (Werte 0 bis 1023)
#define SWITCH 1
#define PHOTO  2  // 1023 = ganz dunkel, 0 = sehr hell

#define Input1 A0
#define Input2 A1
#define Input3 A2
#define Input4 A3
#define Poti   A7
int poti;

void setup() {

  // Serial.begin(115200);
  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(Led1, OUTPUT);
  pinMode(Led2, OUTPUT);
  pinMode(Led3, OUTPUT);
  pinMode(LedIntern, OUTPUT);
  
  // Display initialisieren
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(0,0);
  display.print("   Minicontroller");
  display.display();

  // Motoren abschalten
  // motor(MotorA, 0, STOP);
  // motor(MotorB, 0, STOP); 

  // LEDS ausschalten
  // led(Led1, 0);
  // led(Led2, 0);
  // led(Led3, 0);

  // Poti einlesen
  // poti = analogRead(Poti);
  // Serial.print("Poti: ");
  // Serial.println (poti);

}

void loop() {
  digitalWrite(LedIntern, HIGH);
  delay(500);
  digitalWrite(LedIntern, LOW);
  delay(500);
}

// Eingänge
int input(int port, int func) {
  if (func == SWITCH) {
    if (analogRead(port) < 50) return 1;
    else return 0;
  }
  else if (func == PHOTO) {
    return(analogRead(port));
  }
  else {
    
  }
}

// LED Steuerung
void led(int lednum, int brightness) {
  if ( (lednum == Led1) || (lednum == Led2) || (lednum == Led3) ) {
    analogWrite(lednum, brightness);
  }
}

// Motorsteuerung
void motor(int motornum, int speed, int direction) {
  if (speed > 255) speed = 255;
  if (speed < 0) speed = 0;
  if (motornum == MotorA) {
    if (direction == FORWARD) {
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      analogWrite(enA, speed);
    }
    else if (direction == BACKWARD) {
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      analogWrite(enA, speed);
    }
    else {
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      analogWrite(enA, 0);
    }
  }
  if (motornum == MotorB) {
    if (direction == FORWARD) {
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      analogWrite(enB, speed);
    }
    else if (direction == BACKWARD) {
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      analogWrite(enB, speed);
    }
    else {
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      analogWrite(enB, 0);
    }
  }
}
