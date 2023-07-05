#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10);  // Set CE and CSN pins

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(0xF0F0F0F0E1LL);  // Set the address for communication
}

void loop() {
  char text[] = "Hello NRF!";  // Message to be sent

  radio.stopListening();  // Put the module in transmitting mode
  bool success = radio.write(&text, sizeof(text));  // Send the message

  if (success) {
    Serial.println("Message sent successfully.");
  } else {
    Serial.println("Failed to send message.");
  }

  delay(1000);
}
