#include <LiquidCrystal.h>
#include <Servo.h>
// RS with 5
// E with 6
// D4 with 8
// D5 with 12
// D6 with 10
// D7 with 11
LiquidCrystal lcd(5,6,8,12,10,11);

Servo myservo;
  
int redled = 2;
int greenled = 3;
int buzzer = 4;
int sensor = A0;
int sensorvalue = 30;
int d = 500;
int potpin = 0;  
int val;

void setup(){
pinMode(redled, OUTPUT);
pinMode(greenled,OUTPUT);
pinMode(buzzer,OUTPUT);
pinMode(sensor,INPUT);
myservo.attach(9);
Serial.begin(9600);
lcd.begin(16,2);
}

void loop(){
  int analogValue = analogRead(sensor);
  Serial.print("gas val : ");
  Serial.print(analogValue);
  
  if(analogValue>sensorvalue){
    //leds
    digitalWrite(redled,LOW);
    digitalWrite(greenled,HIGH);

    //tone
    tone(buzzer,1000,10000);

    //lcd
    lcd.clear();
    delay(d);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Dangerous zone");
    delay(d);

    //servo
    val = analogRead(potpin);            
    val = map(val, 0, 1000, 0, 360);     
    myservo.write(val);
  
  }else{
    //leds
    digitalWrite(greenled,HIGH);
    digitalWrite(redled,LOW);

    //tone
    noTone(buzzer);
    
    //lcd
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("ALL CLEAR");
    delay(d);
    
    //servo
    val = analogRead(potpin);            
    val = map(val, 0, 0, 0, 0);     
    myservo.write(val);
  }       
}
