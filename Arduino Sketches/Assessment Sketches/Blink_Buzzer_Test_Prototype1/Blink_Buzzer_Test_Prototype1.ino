//Define Pins
const int led1 = 1; //Red LED
const int led2 = 2; //Yellow LED
const int led3 = 3; //Green LED
const int buzzer = 4; //Buzzer


void setup() {
  Serial.begin(9600); // Delivering Data from Bluetooth
  Serial1.begin(9600); // Incoming data from Bluetooth
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  // Check if there is incoming serial data
  if (Serial1.available() > 0) 
  {
    String str = Serial1.readString().substring(0); // Read the incoming data as a String

    // Print received data for debugging
    Serial.println("Received data: " + str);
    
    // Check if the received data contains "warning" (case-insensitive)
    if (str.indexOf("Warning") != -1) 
    {
      // Turn on the LED
      digitalWrite(led1, HIGH);
      Serial.println("Warning");
      tone(buzzer, 100);
      delay(1000); // Keep the LED on for 1 second
      noTone(buzzer);
      digitalWrite(led1, LOW); // Turn off the LED
    }
    if (str.indexOf("Caution") != -1)
    { 
      digitalWrite(led2, High);
      Serial.println("Caution");
      tone(buzzer, 100);
      delay(1000);
      noTone(buzzer);
      digitalWrite(led2, LOW);
    }
    if (str.indexOf("Safe") != -1)
    {
      digitalWrite(led3, HIGH);
      Serial.println("Safe");
      delay(1000);
      digitalWrite(led3, LOW)
    }
  }
};