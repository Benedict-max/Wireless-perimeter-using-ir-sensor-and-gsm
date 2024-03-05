#include <SoftwareSerial.h>

// Define pins for SIM800L module
#define SIM800_TX_PIN 6
#define SIM800_RX_PIN 7

// Define pins for sensors
#define SENSOR_1_PIN 2
#define SENSOR_2_PIN 3
#define SENSOR_3_PIN 4
#define SENSOR_4_PIN 5

// Predefined GPS coordinates for each sensor
const float SENSOR_1_LATITUDE = 37.7749;   // Replace with actual latitude
const float SENSOR_1_LONGITUDE = -122.4194; // Replace with actual longitude
const float SENSOR_2_LATITUDE = 34.0522;   // Replace with actual latitude
const float SENSOR_2_LONGITUDE = -118.2437; // Replace with actual longitude
const float SENSOR_3_LATITUDE = 40.7128;   // Replace with actual latitude
const float SENSOR_3_LONGITUDE = -74.0060; // Replace with actual longitude
const float SENSOR_4_LATITUDE = 51.5074;   // Replace with actual latitude
const float SENSOR_4_LONGITUDE = -0.1278;   // Replace with actual longitude

// Initialize SoftwareSerial for communication with SIM800L module
SoftwareSerial sim800lSerial(SIM800_TX_PIN, SIM800_RX_PIN);

void setup() {
  // Start serial communication for debugging
  Serial.begin(9600);
  
  // Set up SoftwareSerial for SIM800L communication
  sim800lSerial.begin(9600);
  
  // Initialize sensors
  pinMode(SENSOR_1_PIN, INPUT);
  pinMode(SENSOR_2_PIN, INPUT);
  pinMode(SENSOR_3_PIN, INPUT);
  pinMode(SENSOR_4_PIN, INPUT);
}

void loop() {
  // Read sensor values
  int sensor1Value = digitalRead(SENSOR_1_PIN);
  int sensor2Value = digitalRead(SENSOR_2_PIN);
  int sensor3Value = digitalRead(SENSOR_3_PIN);
  int sensor4Value = digitalRead(SENSOR_4_PIN);
  
  // Check if any sensor is triggered
  if (sensor1Value == HIGH || sensor2Value == HIGH || sensor3Value == HIGH || sensor4Value == HIGH) {
    // Compose SMS message
    String smsMessage = "Sensor triggered:\n";
    if (sensor1Value == HIGH) {
      smsMessage += "Sensor 1\n";
      smsMessage += "Location: http://maps.google.com/maps?q=" + String(SENSOR_1_LATITUDE, 6) + "," + String(SENSOR_1_LONGITUDE, 6) + "\n";
    }
    if (sensor2Value == HIGH) {
      smsMessage += "Sensor 2\n";
      smsMessage += "Location: http://maps.google.com/maps?q=" + String(SENSOR_2_LATITUDE, 6) + "," + String(SENSOR_2_LONGITUDE, 6) + "\n";
    }
    if (sensor3Value == HIGH) {
      smsMessage += "Sensor 3\n";
      smsMessage += "Location: http://maps.google.com/maps?q=" + String(SENSOR_3_LATITUDE, 6) + "," + String(SENSOR_3_LONGITUDE, 6) + "\n";
    }
    if (sensor4Value == HIGH) {
      smsMessage += "Sensor 4\n";
      smsMessage += "Location: http://maps.google.com/maps?q=" + String(SENSOR_4_LATITUDE, 6) + "," + String(SENSOR_4_LONGITUDE, 6) + "\n";
    }
    
    // Send SMS
    sendSMS(smsMessage);
  }
  
  // Delay before next sensor reading
  delay(1000);
}

// Function to send SMS
void sendSMS(String message) {
  // AT command to set SMS mode
  sim800lSerial.println("AT+CMGF=1");
  delay(1000);
  
  // AT command to set recipient number
  sim800lSerial.println("AT+CMGS=\"+254706557454\""); // Replace with recipient number
  delay(1000);
  
  // Send message
  sim800lSerial.println(message);
  delay(1000);
  
  // End message with CTRL+Z
  sim800lSerial.println((char)26);
  delay(1000);
}
