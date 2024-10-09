#include <Arduino.h>
#include <SPI.h>

void setup() {
  while (!Serial) {
    yield();
  }
  Serial.begin(9600);
  pinMode(12, OUTPUT);
  SPCR |= _BV(SPE);
  SPI.attachInterrupt();
}

volatile byte recvdData = 0;
volatile bool recvd = false;

ISR (SPI_STC_vect) {
  recvdData = SPDR;
  recvd = true;
}

void loop() {
  if (recvd) {
    Serial.println(recvdData);
    recvd = false;
  }
}
