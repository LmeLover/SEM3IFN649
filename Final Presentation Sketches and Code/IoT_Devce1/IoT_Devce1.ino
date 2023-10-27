/*
IoT Device 1, the temperature and tilt sensors.
The temperature sensor is located inside the cooler bag.
The tri-axis accelerometer is placed on the side of the bag using velcro.
*/
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 1

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
int currentMode = 1; // Initialize in Mode 1 (Temp & Tilt)

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600); // Initialize Bluetooth serial
  sensors.begin();
}

void loop() {
  // Check for data from Serial (for testing modes)
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    handleCommand(command);
  }

  // Check for data from Bluetooth serial
  if (Serial1.available()) {
    String btCommand = Serial1.readStringUntil('\n');
    handleCommand(btCommand);
  }

  // Reading from sensors and sending data based on mode
  switch (currentMode) {
    case 0:  // OFF
      Serial.println("[OFF]");
      Serial1.println("[OFF]");  // Send via Bluetooth
      delay(1000);
      break;

    case 1:  // Temp & Tilt
    {
      String tempReading = readTemperature();
      String posReading = readPosition();

      // Sending structured string message
      String messageToSend = "[M1]|" + tempReading + "|" + posReading;
      Serial.println(messageToSend);
      Serial1.println(messageToSend);  // Sending via Bluetooth
      delay(1000);
      break;
    }

    case 2:  // Temp Only
    {
      String tempReading = readTemperature();

      // Sending structured string message
      String messageToSend = "[M2]|" + tempReading;
      Serial.println(messageToSend);
      Serial1.println(messageToSend);  // Sending via Bluetooth
      delay(1000);
      break;
    }

    case 3:  // Tilt Only
    {
      String posReading = readPosition();

      // Sending structured string message
      String messageToSend = "[M3]|" + posReading;
      Serial.println(messageToSend);
      Serial1.println(messageToSend);  // Sending via Bluetooth
      delay(1000);
      break;
    }
  }
}

void handleCommand(String command) {
  if (command == "M0") {
    currentMode = 0;
  } else if (command == "M1") {
    currentMode = 1;
  } else if (command == "M2") {
    currentMode = 2;
  } else if (command == "M3") {
    currentMode = 3;
  }
  // You can expand this function to handle other commands in the future if needed
}

String readTemperature() {
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);
  String tempStatus;
//Logic for Temperature Read-out. Can be changed depending on the temperature requirements. These are based on refrigerated food safety.
  if (tempC < 4) {
    tempStatus = "[OK]";
  } else if (tempC >= 4 && tempC < 8) {
    tempStatus = "[!]";
  } else {
    tempStatus = "[!!!]";
  }

  return "TEMP:" + String(tempC, 1) + "°C" + tempStatus;
}

//Depending on the orientation of how you position your tilt sensor these values will need to change.
String readPosition() {
  int yValue = analogRead(19);
  if (yValue > 600) {
    return "POS:[Stable]";
  } else if (yValue <= 600 && yValue > 570) {
    return "POS:[Tilted]";
  } else {
    return "POS:[Tipped]";
  }
}
