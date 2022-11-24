#include <Servo.h>

String command;
int mvalue;
int svalue;

#define ledPin 13

Servo myservo;

void setup()
{

  pinMode(3, OUTPUT); // PWM 1
  pinMode(5, OUTPUT); // PWM 2
  pinMode(8, OUTPUT); // MOT 1 pin 10
  pinMode(7, OUTPUT); // MOT 1 pin 10
  pinMode(4, OUTPUT); // MOT 2 pin 9
  pinMode(2, OUTPUT); // MOT 2 pin 9
  pinMode(ledPin, OUTPUT);
  myservo.attach(6);

  Serial.begin(9600);

  // put your setup code here, to run once:
}

void loop()
{
  if (Serial.available())
  {
    command = Serial.readStringUntil('\n');
    command.trim();

    if (command.equals("Pressed_A_1"))
    {
      //      Serial.println("Dioda wlaczona");
      digitalWrite(ledPin, HIGH);
    }

    else if (command.equals("Pressed_A_0"))
    {
      //      Serial.println("Dioda wylaczona");
      digitalWrite(ledPin, LOW);
    }

    if (command.indexOf("rbumper_") >= 0)
    {

      digitalWrite(8, LOW);
      digitalWrite(7, HIGH);
      digitalWrite(4, LOW);
      digitalWrite(2, HIGH);

      command = command.substring(8);
      mvalue = command.toInt();
      mvalue = mvalue * 255 / 100;
      analogWrite(5, mvalue);
      analogWrite(3, mvalue);
    }

    if (command.indexOf("lbumper_") >= 0)
    {

      digitalWrite(8, HIGH);
      digitalWrite(7, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(2, LOW);

      command = command.substring(8);
      mvalue = command.toInt();
      mvalue = mvalue * 255 / 100;
      Serial.println(mvalue);
      analogWrite(5, mvalue);
      analogWrite(3, mvalue);
    }
    if (command.indexOf("leftStickX_") >= 0)
    {

      command = command.substring(11);
      svalue = command.toInt();
      svalue = svalue * 255 / 100;
      svalue = map(svalue, 0, 255, 0, 150);

      myservo.write(svalue);
    }
  }
  // put your main code here, to run repeatedly:
}
