/*
  Receiver code
*/

#include <Arduino.h>
#include <SPI.h>

void SPI_setup(void);

char buffer[20];
volatile short int index = 0;
volatile short int data_is_received = 0;
volatile short int terminator_is_received = 0;
short int buffer_size = sizeof(buffer);

#define SPI_data_buffer SPDR
#define terminator '\0'

void setup()
{
  // put your setup code here, to run once:
  SPI_setup();
  Serial.begin(9600);
}

void loop()
{
  // put your main code here, to run repeatedly:
  if (data_is_received && index < buffer_size)
  {
    buffer[index] = SPI_data_buffer; // This also clear the interrupt flag
    index++;
    if (buffer[index] == terminator || index >= buffer_size)
    {
      index = 0;
      // String s = String(buffer); // If you want to convert the buffer into a string
      Serial.print(buffer);
    }
    data_is_received = 0;
  }
}

ISR(SPI_STC_vect)
{                    // SPI interrupt routine
  data_is_received = 1; // Note that the ISR should be as fast as possible
}

void SPI_setup(void)
{
  pinMode(MISO, OUTPUT); // To send to the controller(master)
  SPCR |= _BV(SPE);      // This bit must be set to enable any SPI operations.
  SPI.attachInterrupt(); // turn on interrupt (SPCR |= _BV(SPIE))
}