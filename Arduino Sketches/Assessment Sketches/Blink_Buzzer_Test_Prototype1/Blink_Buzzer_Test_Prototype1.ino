//Define Pins
const int led1 = 1; //Red LED
const int led2 = 2; //Yellow LED
const int led3 = 3; //Green LED
const int buzzer = 4; //Buzzer


void setup() {
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  // Check if there is incoming serial data
  if (Serial.available() > 0) {
    String receivedData = Serial.readString(); // Read the incoming data as a String

    // Print received data for debugging
    Serial.println("Received data: " + receivedData);
    
    // Check if the received data contains "warning" (case-insensitive)
    if (receivedData.indexOf("Warning") != -1) {
      // Turn on the LED
      digitalWrite(led1, HIGH);
      delay(1000); // Keep the LED on for 1 second
      digitalWrite(led1, LOW); // Turn off the LED
    }
  }
}