// #include <SPI.h>
// #include <nRF24L01.h>
// #include <RF24.h>

// RF24 radio(7, 8);  // Set CE and CSN pins

// void setup() {
//   Serial.begin(9600);
//   radio.begin();
//   radio.openWritingPipe(0xF0F0F0F0E1LL);  // Set the address for communication
// }

// void loop() {
//   char text[] = "Hello Orchi!";  // Message to be sent

//   radio.stopListening();  // Put the module in transmitting mode
//   bool success = radio.write(&text, sizeof(text));  // Send the message

//   if (success) {
//     Serial.println("Message sent successfully.");
//   } else {
//     Serial.println("Failed to send message.");
//   }

//   delay(1000);
// }


#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <DHT.h>

#define DHTPIN 2        // Pin connected to the DHT11 data pin
#define DHTTYPE DHT11   // DHT11 sensor type
DHT dht(DHTPIN, DHTTYPE);

RF24 radio(7, 8);  // Set CE and CSN pins

struct SensorData {
  float temperature;
  float humidity;
};

void setup() {
  Serial.begin(9600);
  dht.begin();
  radio.begin();
  radio.openWritingPipe(0xF0F0F0F0E1LL);  // Set the address for communication
  radio.setPALevel(RF24_PA_HIGH);  // Set the power amplifier level
  radio.stopListening();  // Put the module in transmitting mode
}

void loop() {
  float temperature = dht.readTemperature();  // Read temperature value
  float humidity = dht.readHumidity();        // Read humidity value

  SensorData data;
  data.temperature = temperature;
  data.humidity = humidity;

  bool success = radio.write(&data, sizeof(data));  // Send the data

  if (success) {
    Serial.println("Message sent successfully.");
  
  } else {
    Serial.println("Failed to send message.");
  }

  delay(2000);  // Wait for 2 seconds before sending the next reading
}
