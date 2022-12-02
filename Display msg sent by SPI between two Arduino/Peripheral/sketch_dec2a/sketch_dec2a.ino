/* RECEIVER */


#include <SPI.h>

char buffer[20];
volatile short int index = 0;
volatile short int data_received = 0;
volatile short int terminator_received = 0;
short int buffer_size = sizeof(buffer);

#define SPI_data_buffer SPDR
#define terminator '\0'

void setup() {
  // put your setup code here, to run once:
  //SPI.begin();
  SPI_setup();
  Serial.begin(9600);
  Serial.println("Arduino 2: this is slave");
}

void loop() {
  // put your main code here, to run repeatedly:

  if (data_received && index < buffer_size) {
    buffer[index] = SPI_data_buffer;  // This also clear the interrupt flag
    index++;
    if (buffer[index] == terminator || index >= buffer_size) {
      index = 0;
      //String s = String(buffer); // If you want to convert the buffer into a string
      Serial.print(buffer);
      //Serial.println();
    }
    data_received = 0;
  }
}
ISR(SPI_STC_vect) {   // SPI interrupt routine
  data_received = 1;  // Note that the ISR should be as fast as possible
}

void SPI_setup(void) {
  pinMode(MISO, OUTPUT);  // To send to the controller(master)
  SPCR |= _BV(SPE);       // This bit must be set to enable any SPI operations.
  SPI.attachInterrupt();  // turn on interrupt (SPCR |= _BV(SPIE))
}

/*Quiz
Try to make the sender sends the data size before sending the data
and in the receiver side, use malloc to adjust the buffer size
it makes the communication more flexable
*/
