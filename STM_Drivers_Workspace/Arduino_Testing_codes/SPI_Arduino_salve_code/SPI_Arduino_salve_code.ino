#include <SPI.h>

#define BUFFER_SIZE 100
//char dataBuff[BUFFER_SIZE];
int buff[10];
int i;

void SPI_SlaveInit() {
  pinMode(MISO, OUTPUT); // MISO output
  pinMode(MOSI, INPUT);
  pinMode(SCK, INPUT);
  pinMode(SS, INPUT);

  SPCR |= (1 << SPE);  // SPI Enable in Slave mode
}


void setup() {
  Serial.begin(9600);
  SPI_SlaveInit();
  Serial.println("Slave Initialized");
}

void loop() {
  i = 0;
  Serial.println("Waiting for Master...");
  while (digitalRead(SS) == HIGH); // Wait for master to pull SS low

  delayMicroseconds(50); // Let SPI master get ready

  while (i < 10) {
    if (SPSR & (1 << SPIF)) {
      buff[i++] = SPDR; // Read exactly once when SPIF is set
    }
  }

  Serial.println("Received");
  for (int j = 0; j < 10; j++) {
    Serial.println(buff[j]);
  }

  delay(1000);
}

