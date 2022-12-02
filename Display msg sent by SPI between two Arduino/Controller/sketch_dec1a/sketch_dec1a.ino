/* SENDER */

#include <SPI.h>

volatile short int ACK = 0;

void setup() {
  // put your setup code here, to run once:

  // Enable chip select
  digitalWrite(SS, HIGH); /*When a device's Chip Select pin is low, it communicates with the Controller.
                           When it's high, it ignores the Controller*/
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV8);  // clk rate /= 8 (16/8 = 2Mhz)

  Serial.begin(9600);
  Serial.println("hello from controller");
}

void loop() {
  // put your main code here, to run repeatedly:

  // Do not forget to write digitalWrite(SS,LOW) before sending

  ACK = SPI_send("Hello_From_Shady\r");  // This \r used to get to the next line in the receiver's serial
  if (ACK == 0) {
    Serial.println("Sent successfully");
  }
  delay(500);
}

int SPI_send(String str) {
  digitalWrite(SS, LOW);  // enable Slave Select
  for (int i = 0; i < str.length(); i++) {
    SPI.transfer(str[i]);
    Serial.println(str[i]);
    delay(5);
  }
  digitalWrite(SS, HIGH);  // disable Slave Select
  return 0;
}

/*Quiz
Try to make the sender sends the data size before sending the data
and in the receiver side, use malloc to adjust the buffer size
it makes the communication more flexable
*/
