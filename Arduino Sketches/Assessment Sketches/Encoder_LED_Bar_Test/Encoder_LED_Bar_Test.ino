#define outputA 5
#define outputB 6

int counter = 0;
int aState;
int aLastState;

const int minValue = 0;
const int maxValue = 10;

// Define the LED bar pins
const int DI_PIN = 1;   // Replace with the actual DI pin number
const int DCKI_PIN = 0; // Replace with the actual DCKI pin number

void setup() {
  pinMode(outputA, INPUT);
  pinMode(outputB, INPUT);

  // Set the DI and DCKI pins as OUTPUT
  pinMode(DI_PIN, OUTPUT);
  pinMode(DCKI_PIN, OUTPUT);

  Serial.begin(9600);
  aLastState = digitalRead(outputA);
}

void loop() {
  aState = digitalRead(outputA);
  if (aState != aLastState) {
    if (aState == LOW) {
      if (digitalRead(outputB) == LOW) {
        if (counter > minValue) {
          counter--;
        }
      } else {
        if (counter < maxValue) {
          counter++;
        }
      }
      Serial.print("Position: ");
      Serial.println(counter);
    }
    aLastState = aState;
  }

  // Control the LED bar based on the counter value
  updateLEDBar();
}

void updateLEDBar() {
  // Control the LED bar using DI and DCKI
  digitalWrite(DCKI_PIN, LOW); // Set DCKI low to start data transmission
  for (int i = 0; i < 10; i++) {
    // Send the data for each LED, based on the counter value
    digitalWrite(DI_PIN, i < counter ? HIGH : LOW);
    digitalWrite(DCKI_PIN, HIGH); // Set DCKI high to latch the data
    digitalWrite(DCKI_PIN, LOW);  // Set DCKI low to prepare for the next data bit
  }
}
