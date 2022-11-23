#include <SPI.h>
//#include <Servo.h>

byte buff [3]; // 3 byte to receive
volatile byte index = 0;
volatile boolean process = false;
int Fwidth = 0;
int Bwidth = 0;
int Swidth = 0;

//Servo myservo;


void setup() {

//  myservo.attach(3);
  Serial.begin(115200);
  SPI.setClockDivider(SPI_CLOCK_DIV64);
  // Set the Master in Slave out as an output
  pinMode(MISO, OUTPUT);

  pinMode(10, OUTPUT); // PWM 1
  pinMode(9, OUTPUT); // PWM 2
  pinMode(8, OUTPUT); // MOT 1 pin 10
  pinMode(7, OUTPUT); // MOT 1 pin 10
  pinMode(3, OUTPUT); // MOT 2 pin 9
  pinMode(2, OUTPUT); // MOT 2 pin 9

  SPCR |= _BV(SPE);  // Turn SPI in Slave Mode

  SPI.attachInterrupt();

}

ISR (SPI_STC_vect) { // SDPR - value from master
  byte c = SPDR;
  SPDR = SPDR + 10;
  buff[index] = SPDR; // read byte from SPI Data Register
  index++;
  if (index == 3) {
    index = 0;
    process = true;
  }
  delay(50);
}

void loop () {

  if (process) {
    process = false;
        Serial.println(buff[0], DEC);
        Serial.println(buff[1], DEC);
        Serial.println(buff[2], DEC);
  }

  if (buff[0] == 0xAA & buff[2] == 0xFF) {
    digitalWrite(8, LOW);
    digitalWrite(7, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(2, HIGH);

    Fwidth = buff[1] * 255 / 100;
    analogWrite(10, Fwidth);
    analogWrite(9, Fwidth);
    Serial.println(Fwidth);
    delay(50);
  }

  else if (buff[0] == 0xBB & buff[2] == 0xFF) {
    digitalWrite(8, HIGH);
    digitalWrite(7, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(2, LOW);

    Bwidth = buff[1] * 255 / 100;
    analogWrite(10, Bwidth);
    analogWrite(9, Bwidth);
    Serial.println(Bwidth);
    delay(50);
  }

  //  if (buff[0] == 0x0 & buff[1] == 0x0 & buff[2] == 0x0) {
  //    buff[0] = 0;
  //    buff[1] = 0;
  //    buff[2] = 0;
  //    digitalWrite(9, LOW);
  //    digitalWrite(6, LOW);
  //    delay(50);
  //  }

//  if (buff[0] == 0xCC & buff[2] == 0xFF) {
//    Swidth = buff[1] * 255 / 100;
//    Swidth = map(Swidth, 0, 255, 0, 150);
//    myservo.write(Swidth);
//    //    Serial.println(Swidth);
//    delay(50);
//  }


}
