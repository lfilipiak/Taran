#include <SPI.h>

byte buff [1]; // 3 byte to receive
volatile byte index = 0;
volatile boolean process = false;

void setup() {

  //  myservo.attach(3);
  Serial.begin(115200);
  // Set the Master in Slave out as an output
  SPI.setClockDivider();
  pinMode(MISO, OUTPUT);

  SPCR |= _BV(SPE);  // Turn SPI in Slave Mode

  SPI.attachInterrupt();
}

ISR (SPI_STC_vect) { // SDPR - value from master
  byte c = SPDR;
//  SPDR = SPDR + 10;
  buff[index] = SPDR; // read byte from SPI Data Register
  index++;
  if (index == 1) {
    index = 0;
    process = true;
  }
}

void loop () {

  if (process) {
    Serial.println(SPDR, DEC);
    process = false;
//    Serial.println(buff[0], DEC);
  }
}
