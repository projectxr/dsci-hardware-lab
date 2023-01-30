#define button 2
//int value = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(button, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = digitalRead(button);
  if(val == 0)
  {
    Serial.println("A");

    delay(200);
  }
  else if(val == 1)
  {
    Serial.println("a");
    delay(200);

  }
  delay(200);
}
