int previousValue; //ultimo misuramento
int currentValue; //valore corrente
Servo myservo; 
int flexSensor=0;

int noise = 350;//se il prossimo rilevamento è cambia meno di 350, viene scartato

void setup() {
  pinMode(flexSensor, INPUT);
  previousValue = analogRead(flexSensor);
  currentValue = previousValue;
  expectedValue = previousValue;
  
  myservo.attach(9);
  
  Serial.begin(9600); 
}

void loop() {
  currentValue = analogRead(flexSensor);
  if( abs(currentValue-previousValue) > noise){ //abs è la funzione modulo abs(-5) == 5
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
