#include <Servo.h>

#define green_led 7
#define red_led 6
  Servo myservo;
int pos = 0; 

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(green_led, OUTPUT);
  pinMode(red_led, OUTPUT);

  myservo.attach(9);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  if(Serial.available())
  {
    char val = Serial.read();
    Serial.println(val);
    //myservo.write(180);
    if(val == 'A')
    {
      digitalWrite(green_led, HIGH);
      digitalWrite(red_led, LOW);
      myservo.write(0);

      digitalWrite(red_led, HIGH);
      digitalWrite(green_led, LOW);


    }
    else if(val == 'a')
    {
           digitalWrite(green_led, HIGH);
      digitalWrite(red_led, LOW);
      myservo.write(100);
    

    }
  }
}
