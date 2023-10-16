#define outputA 5
#define outputB 6

int counter = 0;
int aState;
int aLastState;

const int minValue = 0;
const int maxValue = 8;

void setup() {
  pinMode(outputA, INPUT);
  pinMode(outputB, INPUT);

  Serial.begin(9600);
  aLastState = digitalRead(outputA);
}

void loop() {
  aState = digitalRead(outputA);
  if (aState != aLastState) {
    if (aState == LOW) {
      // Increment the counter when the encoder reaches a full detent position (click)
      if (digitalRead(outputB) == LOW) {
        if (counter > minValue) { // Limit to a minimum value of 0
          counter--;
        }
      } else {
        if (counter < maxValue) { // Limit to a maximum value of 10
          counter++;
        }
      }
      Serial.print("Position: ");
      Serial.println(counter);
    }
    aLastState = aState;
  }
}
