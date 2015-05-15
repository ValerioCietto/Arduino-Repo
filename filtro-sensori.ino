int previousValue;
int currentValue;
Servo myservo; 

int noise = 350;//how much the peak are high 

void setup() {
  previousValue = analogRead(0);
  currentValue = previousValue;
  expectedValue = previousValue;
  
  myservo.attach(9);
  
  Serial.begin(9600); 
}

void loop() {
  currentValue = analogRead(0);
  if( abs(currentValue-previousValue) > noise){
    previousValue=currentValue;  
  }
  else{
    currentValue=previousValue; 
  } 
  Serial.print("current value: ");
  Serial.println(currentValue);
  currentValue = map(currentValue, 300, 1023, 0, 180);
  myservo.write(currentValue);
  delay(100);
}
