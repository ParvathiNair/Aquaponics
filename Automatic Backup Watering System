const int VAL_PROBE = 0; //Analog pin 0
const int MOISTURE_LEVEL = 250; // the value after the LED goes on

void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(7, OUTPUT);
}

void LedState(int state)
{
  digitalWrite(13,state);
}

void loop()
{
  int moisture = analogRead(VAL_PROBE);
  
  Serial.print("Moisture = ");
  Serial.println(moisture);
  
  if(moisture > MOISTURE_LEVEL)
  {
    LedState(HIGH);
    digitalWrite(7,HIGH);
  }
  else 
  {
    LedState(LOW);
    digitalWrite(7,LOW);
  }
  
  delay(500);
}
