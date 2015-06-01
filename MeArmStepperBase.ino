/*
*/
/*
pin layout
0 tx
1 rx
2 servo1
3 servo2
4 servo3
5
6
7 
8 
9 
10 
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
#include <Stepper.h>

const int stepsPerRevolution = 2048;
Stepper spalla(stepsPerRevolution, 5,11,6,13);

int reflex=210;
boolean ledOn = false; //debug boolean
boolean executing = false; //stops reading if the robot is moving to prevent long queues

Servo chela;
boolean chelaopen = false;

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
  //chela.attach(2);
  //gomito.attach(3);
  //avambraccio.attach(4);
  spalla.setSpeed(14);
  
}
void loop()
{
  
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
          //if(spallapos<180){
             spallapos=spallapos-10;
             spalla.step(-10);
             
          //}
          
        }
        else if(msg=='a'){
          Serial.println(msg);
          //if(spallapos>0){
             spallapos=spallapos+10;
             spalla.step(10);
             
          //}
          
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
