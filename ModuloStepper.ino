
#include <Stepper.h>

const int stepsPerRevolution = 2048;  

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 10,9, 11);

int stepperSpeed = 14; //1...14
int delayTime = 10; //10...24*60*60*1000
String mode = 
"loop cc"
//"loop ccw"
//"1cc,1ccw"
;
int posizione=0;
int giro = 0;
boolean stopFlag=false;

void setup() {
  // set the speed at 60 rpm:
  myStepper.setSpeed(stepperSpeed);
  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {
  
  if(mode == "loop cc"){
    Serial.println("clockwise");
    myStepper.step(1);
    if(posizione<stepsPerRevolution){
      posizione++;
    }  
    else{
      posizione=0; 
    }  
    delay(delayTime);
  }
  else if(mode == "loop ccw"){
    Serial.println("counterclockwise");
    myStepper.step(-1);
    if(posizione>0){
      posizione--;
    }  
    else{
      posizione=stepsPerRevolution; 
    }
    delay(delayTime);
  }
  else if(mode == "60cc, 60ccw"){
    for(int i =0; i<341;i++){
      Serial.println("clockwise");
      myStepper.step(1);
      if(posizione<stepsPerRevolution){
        posizione++;
      }  
      else{
        posizione=0; 
      }  
      delay(delayTime);
    }
    for(int i =0; i<341;i++){
      Serial.println("counterclockwise");
      myStepper.step(-1);
    if(posizione>0){
      posizione--;
    }  
    else{
      posizione=stepsPerRevolution; 
    }
    delay(delayTime);
    }
    
  }
  else if(mode == "1cc,1ccw"){
    Serial.println("1cc,1ccw");
    myStepper.step(-1);
    delay(delayTime);
  }
}
