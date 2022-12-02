/*
  Sender code
*/
#define ready 'r'
int seq = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);  //Initiate the UART;
}

void loop() {
  // put your main code here, to run repeatedly:
    while (Serial.available() < 1)
      ;
    if (Serial.read() == ready) {
      Serial.println("shady");
  }
  seq++;
}