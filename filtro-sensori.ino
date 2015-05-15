int previousValue;
int currentValue;
int expectedValue;

int noise = 10;

void setup() {
  previousValue = analogRead(0);
  currentValue = previousValue;
  expectedValue = previousValue;
}

void loop() {
  currentValue = analogRead(0);
  if( abs(currentValue-previousValue) > noise){
    previousValue=currentValue;  
  }
  else{
    currentValue=previousValue; 
  }  
}
