#include<UltraDistSensor.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);
const int stepPin=13;
const int dirPin=12; 
const int enablePin=5 ;
const int rightSensorPin=7;
const int leftSensorPin=8;
const int echoPin = 2;
const int trigPin = 3;
const int stepsPerRevolution = 200;
const int numberOfSteps = stepsPerRevolution/8;
boolean rightsensor = 0;
boolean leftsensor = 0;
long duration;
int distance;
void turn()
{
for(int i= 0; i < numberOfSteps; i++)
{
digitalWrite(stepPin,HIGH);
38
delayMicroseconds(10000);
digitalWrite(stepPin, LOW);
delayMicroseconds(10000);
}
}
void ultrsonic()
{
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW); 
duration = pulseIn(echoPin, HIGH);
distance = duration * 0.034 / 2;
}
void zero()
{
rightsensor = 0;
leftsensor = 0;
}
void Display();
{
lcd.setCursor(0,0); 
39
lcd.print("Distance: ");
lcd.print(distance);
lcd.print(" cm");
}
void setup()
{
pinMode (stepPin, OUTPUT);
pinMode (dirPin, OUTPUT);
pinMode (enablePin, OUTPUT);
pinMode(leftSensorPin, INPUT);
pinMode(rightSensorPin, INPUT);
pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT);
lcd.backlight();
lcd.init();
digitalWrite(enablePin, LOW);
Serial.begin (9600);
} 
void loop ()
{
 ultrsonic();
 Display();
 rightsensor =digitalRead(rightSensorPin);
40
 leftsensor =digitalRead(leftSensorPin);
 
if (leftsensor==LOW && rightsensor==HIGH)
{
Serial.println("Turning Right");
digitalWrite(dirPin,LOW);
turn();
delayMicroseconds(100);
zero();
}
else if (leftsensor==HIGH && rightsensor==LOW)
{
Serial.println("Turning Left");
digitalWrite(dirPin,HIGH);
turn();
delayMicroseconds(100);
zero();
}
else 
{
zero();
}
}