/*
from Example Bluetooth Serial Passthrough Sketch
by: Jim Lindblom
SparkFun Electronics
date: February 26, 2013
license: Public domain
This example sketch converts an RN-42 bluetooth module to
communicate at 9600 bps (from 115200), and passes any serial
data between Serial Monitor and bluetooth module.
from Arduino Motor Shield Tutorial
avaible at http://www.instructables.com/id/Arduino-Motor-Shield-Tutorial/
from Servo tutorial
*/
#include <SoftwareSerial.h>
#include <Servo.h>
/*
pin layout
0 tx
1 rx
2 bt tx //yellow
3 pwm A
4 bt rx //green
5 trig pin
6 echo pin
7 servo signal
8 brake B
9 brake A
10
11 pwm B
12 dir A
13 dir B
A0
A1
A2
A3
A4
A5
The program requires that the RN42 bluetooth chip has the Tx pin linked to the 2 pin and the Rx pin linked to the 4 pin
*/
int bluetoothTx = 2; // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 4; // RX-I pin of bluetooth mate, Arduino D3
int reflex=210;
boolean ledOn = false; //debug boolean
boolean executing = false; //stops reading if the robot is moving to prevent long queues
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
Servo myservo; // create servo object to control a servo
void setup()
{
Serial.begin(9600); // Begin the serial monitor at 9600bps
delay(2000);
digitalWrite(13,HIGH);
bluetooth.begin(115200); // The Bluetooth Mate defaults to 115200bps
bluetooth.print("$"); // Print three times individually
bluetooth.print("$");
bluetooth.print("$"); // Enter command mode
delay(400); // Short delay, wait for the Mate to send back CMD
bluetooth.println("U,9600,N"); // Temporarily Change the baudrate to 9600, no parity
digitalWrite(13,LOW);
// 115200 can be too fast at times for NewSoftSerial to relay the data reliably
bluetooth.begin(9600); // Start bluetooth serial at 9600
bluetooth.print("---");
myservo.attach(7); // attaches the servo on pin 9 to the servo object
pinMode(12, OUTPUT); //Initiates Motor Channel A pin
pinMode(9, OUTPUT); //Initiates Brake Channel A pin
pinMode(13, OUTPUT); //Initiates Motor Channel B pin
pinMode(8, OUTPUT); //Initiates Brake Channel B pin
pinMode(3, OUTPUT); //pwmA
pinMode(11, OUTPUT); //pwmB
pinMode(5, OUTPUT);
pinMode(6, INPUT);
}
void loop()
{
long duration, distance;
digitalWrite(3,LOW);
digitalWrite(11,LOW);
digitalWrite(5, LOW); // Added this line
delayMicroseconds(2); // Added this line
digitalWrite(5, HIGH);
// delayMicroseconds(1000); - Removed this line
delayMicroseconds(10); // Added this line
digitalWrite(5, LOW);
duration = pulseIn(6, HIGH);
distance = (duration/2) / 29.1;
if (distance >= 200 || distance <= 0){
Serial.println("Out of range");
}
else {
Serial.print(distance);
Serial.println(" cm");
}
//delay(100);
//digitalWrite(12,LOW);
//Serial.println("hello");
//bluetooth.listen();
if(bluetooth.available()){//bluetooth.available()
// Send any characters the Serial monitor prints to the bluetooth
//bluetooth.print("!");//(char)Serial.read()
char msg = (char)bluetooth.read(); //read next character, and removes it from the queue
char next = (char)bluetooth.peek(); //looks for next character, but doesn't eliminate it from the queue
//msg = Serial.read();//serial debugging
if(msg == next){
bluetooth.read();
}
if(executing==false){
if(msg=='d'){ //the characters have been choosen randomly
bluetooth.println(msg);
steerdx(reflex/2);
}
else if(msg=='a'){
bluetooth.println(msg);
steersx(reflex/2);
}
else if(msg=='w'){
bluetooth.println(msg);
forward(reflex);
}
else if(msg=='s'){
bluetooth.println(msg);
backward(reflex);
}
else if(msg=='j'){
bluetooth.println(msg);
myservo.write(70);
}
else if(msg=='f'){
bluetooth.println(msg);
myservo.write(110);
}
else if(msg=='h'){
bluetooth.println(msg);
myservo.write(90);
}
}
else{
}
}
}
void forward(int time){
executing = true;
digitalWrite(12, LOW); //Establishes forward direction of Channel A
digitalWrite(9, LOW); //Disengage the Brake for Channel A
digitalWrite(13, HIGH); //Establishes forward direction of Channel B
digitalWrite(8, LOW); //Disengage the Brake for Channel B
digitalWrite(3,HIGH);//pwmA
digitalWrite(11,HIGH);//pwmB
delay(time);
executing=false;
digitalWrite(9, HIGH); //Disengage the Brake for Channel A
digitalWrite(8, HIGH); //Disengage the Brake for Channel B
}
void forward(int time, int intensity){
executing = true;
digitalWrite(12, LOW); //Establishes forward direction of Channel A
digitalWrite(9, LOW); //Disengage the Brake for Channel A
digitalWrite(13, HIGH); //Establishes forward direction of Channel B
digitalWrite(8, LOW); //Disengage the Brake for Channel B
analogWrite(3,intensity);//pwmA
analogWrite(11,intensity);//pwmB
delay(time);
executing=false;
digitalWrite(9, HIGH); //Disengage the Brake for Channel A
digitalWrite(8, HIGH); //Disengage the Brake for Channel B
}
void backward(int time){
executing = true;
digitalWrite(12, HIGH); //Establishes forward direction of Channel A
digitalWrite(9, LOW); //Disengage the Brake for Channel A
digitalWrite(13, LOW); //Establishes forward direction of Channel B
digitalWrite(8, LOW); //Disengage the Brake for Channel B
digitalWrite(3,HIGH);//pwmA
digitalWrite(11,HIGH);//pwmB
delay(time);
executing=false;
digitalWrite(9, HIGH); //Disengage the Brake for Channel A
digitalWrite(8, HIGH); //Disengage the Brake for Channel B
}
void backward(int time, int intensity){
executing = true;
digitalWrite(12, HIGH); //Establishes forward direction of Channel A
digitalWrite(9, LOW); //Disengage the Brake for Channel A
digitalWrite(13, LOW); //Establishes forward direction of Channel B
digitalWrite(8, LOW); //Disengage the Brake for Channel B
analogWrite(3,intensity);//pwmA
analogWrite(11,intensity);//pwmB
delay(time);
executing=false;
digitalWrite(9, HIGH); //Disengage the Brake for Channel A
digitalWrite(8, HIGH); //Disengage the Brake for Channel B
}
void steerdx(int time){
executing = true;
//digitalWrite(12, HIGH); //Establishes forward direction of Channel A
//digitalWrite(9, LOW); //Disengage the Brake for Channel A
digitalWrite(13, HIGH); //Establishes forward direction of Channel B
digitalWrite(8, LOW); //Disengage the Brake for Channel B
//digitalWrite(3,HIGH);//pwmA
digitalWrite(11,HIGH);//pwmB
delay(time);
delay(reflex/2);
executing=false;
//digitalWrite(9, HIGH); //Disengage the Brake for Channel A
digitalWrite(8, HIGH); //Disengage the Brake for Channel B
}
void steersx(int time){
executing = true;
digitalWrite(12, LOW); //Establishes forward direction of Channel A
digitalWrite(9, LOW); //Disengage the Brake for Channel A
//digitalWrite(13, HIGH); //Establishes forward direction of Channel B
//digitalWrite(8, LOW); //Disengage the Brake for Channel B
digitalWrite(3,HIGH);//pwmA
//digitalWrite(11,HIGH);//pwmB
delay(time);
delay(reflex/2);
executing=false;
digitalWrite(9, HIGH); //Disengage the Brake for Channel A
//digitalWrite(8, HIGH); //Disengage the Brake for Channel B
}  
