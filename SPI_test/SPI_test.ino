#include <SPI.h>

byte buff [4]; // 3 byte to receive
volatile byte index = 0;
volatile boolean process = false;
int width = 0;

void setup() {
  Serial.begin(9600);
  SPI.setClockDivider(SPI_CLOCK_DIV64);
  // Set the Master in Slave out as an output
  pinMode(MISO, OUTPUT);
  //  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT); // PWM
  pinMode(8, OUTPUT); // MOT 1
  pinMode(7, OUTPUT); // MOT 1
  pinMode(6, OUTPUT); // PWM
  pinMode(5, OUTPUT); // MOT 2
  pinMode(4, OUTPUT); // MOT 2
  pinMode(2, OUTPUT);
  

  SPCR |= _BV(SPE);  // Turn SPI in Slave Mode

  SPI.attachInterrupt();
}

ISR (SPI_STC_vect) { // SDPR - value from master
  byte c = SPDR;
  SPDR = SPDR + 10;
  buff[index] = SPDR; // read byte from SPI Data Register
  index++;
  if (index == 4) {
    index = 0;
    process = true;
  }
}

void loop () {




  if (process) {
    process = false;

    Serial.println(buff[0], HEX);
    Serial.println(buff[1], HEX);
    Serial.println(buff[2], HEX);
    Serial.println(buff[3], HEX);
  }



  if ( buff[0] == 0xCC & buff[1] == 0xFF & buff[3] == 10) {
    digitalWrite(8, LOW);
    digitalWrite(7, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(4, HIGH);

    width = buff[2] * 255 / 100;
    analogWrite(9, width);
    analogWrite(6, width);
  }

  else if (buff[0] == 0xDD & buff[1] == 0xFF & buff[3] == 10) {
    digitalWrite(8, HIGH);
    digitalWrite(7, LOW);
    digitalWrite(5, HIGH);
    digitalWrite(4, LOW);

    width = buff[2] * 255 / 100;
    analogWrite(9, width);
    analogWrite(6, width);
  }

  if (buff[0] == 0x0 & buff[1] == 0x0 & buff[2] == 0x0 & buff[2] == 0x0 ) {
    buff[0] = 0;
    buff[1] = 0;
    buff[2] = 0;
    buff[3] = 0;
    digitalWrite(9, LOW);
    digitalWrite(6, LOW);
  }

  if (buff[0] == 0xF5 & buff[1] == 0x00 & buff[3] == 0xB5) {
    width = buff[2] * 255 / 100;
    analogWrite(2, width);
  }

  //  if (buff[0] == 0xF & buff[2] == 0xA) {
  //    if (buff[1] == 0x1) {
  //      digitalWrite(2, HIGH);
  //    }
  //    else if (buff[1] == 0x0) {
  //      digitalWrite(2, LOW);
  //    }
  //  }

  //    if (buff[0] == 0xAA & buff[2] == 0xBB) {
  //      width = buff[1] * 255 / 100;
  //      analogWrite(9, width);
  //      Serial.println(width);
  //    }


  //    if (buff[0] == 0xE & buff[2] == 0xA) {
  //      if (buff[1] == 0x1) {
  //        digitalWrite(4, HIGH);
  //      }
  //      else if (buff[1] == 0x0) {
  //        digitalWrite(4, LOW);
  //      }
  //    }
  //    if (buff[0] == 0xD & buff[2] == 0xA) {
  //      if (buff[1] == 0x1) {
  //        digitalWrite(7, HIGH);
  //      }
  //      else if (buff[1] == 0x0) {
  //        digitalWrite(7, LOW);
  //      }
  //    }
  //    if (buff[0] == 0xC & buff[2] == 0xA) {
  //      if (buff[1] == 0x1) {
  //        digitalWrite(5, HIGH);
  //      }
  //      else if (buff[1] == 0x0) {
  //        digitalWrite(5, LOW);
  //      }
  //    }



}
