#define outputA 5
#define outputB 6

int counter = 0;
int aState;
int aLastState;

const int minValue = 0;
const int maxValue = 8;

// Define the LED pins
int ledPins[] = {20, 19, 18, 17, 16, 15, 14, 13};

void setup() {
  pinMode(outputA, INPUT);
  pinMode(outputB, INPUT);

  Serial.begin(9600);
  aLastState = digitalRead(outputA);

  // Set the LED pins as OUTPUT
  for (int i = 0; i < 8; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
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
      
      // Update LED states based on the counter value
      updateLEDs();
    }
    aLastState = aState;
  }
}

void updateLEDs() {
  // Turn off all LEDs
  for (int i = 0; i < 8; i++) {
    digitalWrite(ledPins[i], LOW);
  }

  // Turn on LEDs up to the current counter value
  for (int i = 0; i < counter; i++) {
    digitalWrite(ledPins[i], HIGH);
  }
}
