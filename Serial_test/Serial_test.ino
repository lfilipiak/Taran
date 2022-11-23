String command;
int value;

#define ledPin 13
#define PWMPin 5

void setup() {

  pinMode(10, OUTPUT); // PWM 1
  pinMode(9, OUTPUT); // PWM 2
  pinMode(8, OUTPUT); // MOT 1 pin 10
  pinMode(7, OUTPUT); // MOT 1 pin 10
  pinMode(3, OUTPUT); // MOT 2 pin 9
  pinMode(2, OUTPUT); // MOT 2 pin 9

  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(PWMPin, OUTPUT);
  // put your setup code here, to run once:

}

void loop() {
  if (Serial.available()) {
    command = Serial.readStringUntil('\n');
    //    command = command.substring(8);
    //    value = command.toInt();
    //    value = value * 255 / 100;
    //    Serial.println(value);
    command.trim();

    if (command.equals("Pressed_A_1")) {
      Serial.println("Dioda wlaczona");
      digitalWrite(ledPin, HIGH);
    }

    else if (command.equals("Pressed_A_0")) {
      Serial.println("Dioda wylaczona");
      digitalWrite(ledPin, LOW);
    }

    if (command.indexOf("rbumper_") >= 0) {

      digitalWrite(8, LOW);
      digitalWrite(7, HIGH);
      digitalWrite(3, LOW);
      digitalWrite(2, HIGH);

      command = command.substring(8);
      value = command.toInt();
      value =  value * 255 / 100;
      analogWrite(10, value);
      analogWrite(9, value);
    }

    if (command.indexOf("lbumper_") >= 0) {

      digitalWrite(8, HIGH);
      digitalWrite(7, LOW);
      digitalWrite(3, HIGH);
      digitalWrite(2, LOW);

      command = command.substring(8);
      value = command.toInt();
      value =  value * 255 / 100;
      analogWrite(10, value);
      analogWrite(9, value);
    }
  }
  // put your main code here, to run repeatedly:

}
