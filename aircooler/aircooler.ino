/* Air cooller project 
updated : 03.12.2013
to be done: - divide loop function to smaller functions
            - test Buz 11A PWM treshold compabilitys 
            
Adafruit lib. for OLED screen & DHT 22 temp./hum. sensor used

*/
  #include <Wire.h>
  #include <Adafruit_GFX.h>
  #include <Adafruit_SSD1306.h>
  #include <DHT.h>

  #define DHTPIN 44 
  #define DHTTYPE DHT22
  #define OLED_DC 11
  #define OLED_CS 12
  #define OLED_CLK 10
  #define OLED_MOSI 9
  #define OLED_RESET 13
  #define pumpPin 2
  #define fan1Pin 3
  #define fan2Pin 4
  Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);// ????
  DHT dht(DHTPIN, DHTTYPE);

  //const int minFanPWM = 150 ;// Use logic level mosFETs. Vtreshhold: 3-4Volts. Othervise use Drivers (Darlington). 
                               //No need for powerfull drivers -it's not time based operationProbably NPN BJT will work just fine

  
  void setup()   
  {                
    Serial.begin(9600);
    dht.begin(); // temperature sensor initialization
    display.begin(); //?????
    display.clearDisplay();//not sure about this line TEST IT
    //pinMode(pumpPin,OUTPUT);
    //pinMode(fan1Pin,OUTPUT);
    //pinMode(fan2Pin,OUTPUT);
  
  //analogWrite(pumpPin, HIGH);//pump water in to radiator for half minute
  //delay(30000); 
  }


  void loop() 
  {
    
    float h = dht.readHumidity(); 
    float t = dht.readTemperature();
    // for debuging
    // Serial.println (h);
    // Serial.println (t); 
  
                                  // function reads from potentiometer and adjusts the value of PWM for fans.  
    int pot = analogRead(A0);     // declare potentiometer pin and and save value of A0 
    
    // folowing loop adjusts fan speed acording to reading from the potentiometer
    // this method gives us abbility to use full spectrum of potentiometer due to treshold of MOSFET 
    if(pot >= 10 && pot <=1023)   // start value 10 just to reduce chances of nioce or pot instability tu turn fans on
       {
       
        analogWrite(fan1Pin, pot/4 );  
        
        analogWrite(fan2Pin, pot/4 );
       
        analogWrite(pumpPin, pot/4 );
       }
   else // if value of pot < 10 then turn fans off
      analogWrite(fan1Pin,0);
      analogWrite(fan2Pin,0);
      analogWrite(pumpPin,0);
  
  //display loop
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
  delay(50);
  }
  
  // measure temperature in water tank & radiator
  // compare them with temperature of the room 
  // inform on display if cooler blocks has to be changed or other 
  
  
 
    
  
