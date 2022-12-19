/*
  * Sender code
*/

#include <Arduino.h>
#include<SPI.h>

void spi_setup(void);
int SPI_send_string(String str);
int spi_send_int(int n);

volatile short int ACK = 0; 

void setup() {
  // put your setup code here, to run once:
  spi_setup();
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i =0 ; i<256 ; i++)
  {
    spi_send_int(i);
    delay(200);
  }
}
void spi_setup(void)
{
  digitalWrite(SS, HIGH); //Disable chip select
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV8);  // clk rate /= 8 (16/8 = 2Mhz)
}

int SPI_send_string(String str) {
  digitalWrite(SS, LOW);  // enable Slave Select
  for (unsigned int i = 0; i < str.length(); i++) {
    SPI.transfer(str[i]);
    Serial.println(str[i]);
    delay(5);
  }
  digitalWrite(SS, HIGH);  // disable Slave Select
  return 0;
}

int spi_send_int(int n)
{
  String str = String(n);
  return SPI_send_string(str);
}