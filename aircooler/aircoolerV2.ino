/*    Air cooller project 
  updated : 17.08.2013
  to be done: - divide loop function to smaller functions

  to do :test Buz 11A PWM treshold compabilitys 
            
  Adafruit lib. for OLED screen & DHT 22 temp./hum. sensor used    
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"
// what pin we're connected to temp/sensor
#define DHTPIN 4 
#define DHTTYPE DHT22
//oled screen pins definition 
#define OLED_DC 11
#define OLED_CS 12
#define OLED_CLK 10
#define OLED_MOSI 9
#define OLED_RESET 13

Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);// ????
DHT dht(DHTPIN, DHTTYPE);

const int minFanPWM = 150 ;// mosfet gate treshhold voltage translated to PWM value ( at the value of 150 gate of mosfet opens the chanel )

int pumpPin = 3; //pump PWM pin 
int fan1Pin = 5; //fan PWM pin
int fan2Pin = 6; // fan PWM pin

void setup()  
{                
  Serial.begin(9600);
  display.begin(); //?????
  display.clearDisplay();//not sure about this line TEST IT
  dht.begin(); // temperature sensor initialization
  
  pinMode(pumpPin,OUTPUT);
  pinMode(fan1Pin,OUTPUT);
  pinMode(fan2Pin,OUTPUT);
  
  //analogWrite(pumpPin, HIGH);//pump water in to radiator for half minute
  //delay(30000); 
}

void loop() 
{
  //declaring variables for DHT sensor
  float h = dht.readHumidity(); 
  float t = dht.readTemperature();

  // function reads from potentiometer and adjusts the value of PWM for fans. 
  // minimal treshold voltage to open MOSFET is about 3 volts so value of analogWrite shold be set to 150  TEST IT 

  int pot = analogRead(A0); // declare potentiometer pin and and save value of A0 in it
  
// folowing loop adjusts fan speed acording to reading from the potentiometer
// this method gives us abbility to use full spectrum of potentiometer due to treshold of MOSFET 
  if(pot >= 10 && pot <=1023)// 
     {
      int speedAdj = (255 - minFanPWM) \ 1024 * pot;
      analogWrite(fan1Pin, minFanPWM+speedAdj ) ;  //turn on the fan
      analogWrite(fan2Pin, minFanPWM+speedAdj );
      }
   else // if value of pot < 10 then turn fans off
      analogWrite(fan1Pin,0);
      analogWrite(fan2Pin,0);
  
  DISPLAY();
  /*display loop
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10,6); //sets start position of the next word
  display.println("TEMP:");
  display.setCursor(10,16);
  display.setTextSize(2);
  display.println(t);
  display.setCursor(10,38);
  display.setTextSize(1);
  display.println("HUM:");
  display.setCursor(10,48);
  display.setTextSize(2);
  display.println(h);
  display.display();
  display.clearDisplay();
  delay(500);
  */
}
  
  // measure temperature in water tank & radiator
  // compare them with temperature of the room 
  // inform on display if cooler blocks has to be changed or other 
  


//display loop function
void DISPLAY (t,h)
{ 
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10,6); //sets start position of the next word
  display.println("TEMP:");
  display.setCursor(10,16);
  display.setTextSize(2);
  display.println(t);
  display.setCursor(10,38);
  display.setTextSize(1);
  display.println("HUM:");
  display.setCursor(10,48);
  display.setTextSize(2);
  display.println(h);
  display.display();
  display.clearDisplay();
  delay(500);
}