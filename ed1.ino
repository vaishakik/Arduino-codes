int state=0;
void setup() {
  pinMode(11, INPUT);
  pinMode(12,OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  state=digitalRead(11);
  if(state==HIGH)
  {
   Serial.print("HIGH\n");
   delay(500);
   
    }
    else
    {
      Serial.print("LOW\n");
      digitalWrite(12,HIGH);
      delay(500);
    
    }

}
