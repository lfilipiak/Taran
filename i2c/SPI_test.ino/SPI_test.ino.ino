#include <SPI.h>

byte buff [3]; // 3 byte to receive
volatile byte index = 0;
volatile boolean process = false;
int width = 0;

void setup() {
  Serial.begin(9600);
  // Set the Master in Slave out as an output
  pinMode(MISO, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);

  int buttonA = 0;
  int buttonB = 0;
  int buttonC = 0;
  int buttonD = 0;

  int myArray[5];

  SPCR |= _BV(SPE);  // Turn SPI in Slave Mode
  SPI.attachInterrupt();
}

ISR (SPI_STC_vect) { // SDPR - value from master
  //  byte c = SPDR;
  SPDR = SPDR + 10;
  buff[index] = SPDR; // read byte from SPI Data Register
  index++;
  if (index == 3) {
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
  }

  if (buff[0] == 0xF & buff[2] == 0xA) {
    if (buff[1] == 0x1) {
      digitalWrite(6, HIGH);
    }
    else if (buff[1] == 0x0) {
      digitalWrite(6, LOW);
    }
  }
  if (buff[0] == 0xE & buff[2] == 0xA) {
    if (buff[1] == 0x1) {
      digitalWrite(4, HIGH);
    }
    else if (buff[1] == 0x0) {
      digitalWrite(4, LOW);
    }
  }
  if (buff[0] == 0xD & buff[2] == 0xA) {
    if (buff[1] == 0x1) {
      digitalWrite(7, HIGH);
    }
    else if (buff[1] == 0x0) {
      digitalWrite(7, LOW);
    }
  }
  if (buff[0] == 0xC & buff[2] == 0xA) {
    if (buff[1] == 0x1) {
      digitalWrite(5, HIGH);
    }
    else if (buff[1] == 0x0) {
      digitalWrite(5, LOW);
    }
  }

  if (buff[0] == 0x5 & buff[2] == 0xA) {
    width = buff[1]*255/100;
    Serial.println(width);
    analogWrite(3, width);   

  }
}









  
  //  byte in_byte;
  //  // SPIF indicates transmission complete (byte received)
  //  if ((SPSR & (1 << SPIF)) != 0) {
  //    in_byte = SPDR;
  // Handle the input code here
  // Set return_val to the value you want to return
  // SPDR = 0x50;
