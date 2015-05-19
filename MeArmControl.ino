/*
*/
/*
pin layout
0 tx
1 rx
2
3
4
5
6
7 left motor direction pin
8 right motor direction pin
9 left motor pwm pin
10 right motor pwm pin
11
12
13
A0
A1
A2
A3
A4
A5
The program requires that the RN42 bluetooth chip has the Tx pin linked to the 2 pin and the Rx pin linked to the 4 pin
*/
#include <Servo.h> 

int reflex=210;
boolean ledOn = false; //debug boolean
boolean executing = false; //stops reading if the robot is moving to prevent long queues

Servo chela;
boolean chelaopen = false;
Servo spalla;
boolean spallaavanti = false;
int spallapos = 90;
Servo gomito;
boolean gomitoavanti = false;
int gomitopos =90;
Servo avambraccio;
boolean avambraccioavanti = false;
int avambracciopos =90;
const int trigPin = 11;
const int echoPin =12;
void setup()
{
  delay(2000);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600); // Start bluetooth serial at 9600
  Serial.print("init");
  digitalWrite(13,HIGH);
  delay(400); // Short delay, wait for the Mate to send back CMD
  digitalWrite(13,LOW);
  chela.attach(9);
  gomito.attach(6);
  avambraccio.attach(10);
  spalla.attach(3);
  spalla.write(90);
  delay(1000);
  gomito.write(90);
  delay(1000);
  chela.write(180);
  Serial.print("ready");
}
void loop()
{
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if(distance<10){
      if(chelaopen){
             chela.write(180);
             chelaopen=false;
      }
  }  
  else{
      if(!chelaopen){
             chela.write(120);
             chelaopen=true;
      }
  }  
  if(Serial.available()){//bluetooth.available()
    // Send any characters the Serial monitor prints to the bluetooth
    //bluetooth.print("!");//(char)Serial.read()
    char msg = (char)Serial.read(); //read next character, and removes it from the queue
    char next = (char)Serial.peek(); //looks for next character, but doesn't eliminate it from the queue
    if(msg == next){
        Serial.read();
      }
      if(executing==false){
        if(msg=='q'){ //the characters have been choosen randomly
          Serial.println(msg);
          if(chelaopen){
             chela.write(180);
             chelaopen=false;
          }
          else{
             chela.write(120);
             chelaopen=true; 
          }  
          
        }
        else if(msg=='d'){
          Serial.println(msg);
          if(spallapos<180){
             spallapos=spallapos-10;
             spalla.write(spallapos);
             
          }
          
        }
        else if(msg=='a'){
          Serial.println(msg);
          if(spallapos>0){
             spallapos=spallapos+10;
             spalla.write(spallapos);
             
          }
          
        }
        else if(msg=='w'){
          Serial.println(msg);
          if(gomitopos<180){
             gomitopos=gomitopos-10;
             gomito.write(gomitopos);
             
          }
          
        }
        else if(msg=='s'){
          Serial.println(msg);
          if(gomitopos>0){
             gomitopos=gomitopos+10;
             gomito.write(gomitopos);
             
          }
      }
       else if(msg=='f'){
          Serial.println(msg);
          if(avambracciopos<180){
             avambracciopos=avambracciopos-10;
             avambraccio.write(avambracciopos);
             
          }
          
        }
        else if(msg=='g'){
          Serial.println(msg);
          if(avambracciopos>0){
             avambracciopos=avambracciopos+10;
             avambraccio.write(avambracciopos);
             
          }
      }
    }
  }
}
