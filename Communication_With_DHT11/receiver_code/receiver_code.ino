// #include <SPI.h>
// #include <nRF24L01.h>
// #include <RF24.h>

// RF24 radio(7, 8);  // Set CE and CSN pins

// void setup() {
//   Serial.begin(9600);
//   radio.begin();
//   radio.openReadingPipe(1, 0xF0F0F0F0E1LL);  // Set the address for communication
//   radio.startListening();  // Put the module in receiving mode
// }

// void loop() {
//   if (radio.available()) {
//     char text[32] = "";  // Buffer to store received message
//     radio.read(&text, sizeof(text));  // Read the received message

//     Serial.print("Received Message: ");
//     Serial.println(text);
//   }
// }

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8);  // Set CE and CSN pins

struct SensorData {
  float temperature;
  float humidity;
};

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, 0xF0F0F0F0E1LL);  // Set the address for communication
  radio.setPALevel(RF24_PA_HIGH);  // Set the power amplifier level
  radio.startListening();  // Put the module in receiving mode
}

void loop() {
  if (radio.available()) {
    SensorData data;  // Create a structure to hold the received data
    radio.read(&data, sizeof(data));  // Read the received data structure

    Serial.print("Received Message: ");
    Serial.print("Temperature: ");
    Serial.print(data.temperature);
    Serial.print("C, Humidity: ");
    Serial.print(data.humidity);
    Serial.println("%");
  }
}
