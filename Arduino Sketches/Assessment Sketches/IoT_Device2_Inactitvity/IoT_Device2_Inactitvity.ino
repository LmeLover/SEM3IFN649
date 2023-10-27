//Define Rotary Encoder Pins. CLK and DT can be swapped depending on the orientaiton of the LEDs.
#define outputA 5 // DT
#define outputB 6 //CLK
#define outputC 4 //SW -The Button


//Set the counter to 0, which is the red LED.
int counter = 0;
int aState;
int aLastState;
int switchState;
int lastSwitchState = HIGH;  // Assuming switch is initially not pressed

const int minValue = 0;
const int maxValue = 3;

// Define LED pins
#define LED0 20
#define LED1 19
#define LED2 18
#define LED3 17

unsigned long lastActivityTime = 0;
const unsigned long TIMEOUT = 5000;  // 5 seconds in milliseconds

void setup() {
    pinMode(outputA, INPUT);
    pinMode(outputB, INPUT);
    pinMode(outputC, INPUT_PULLUP);  // Use INPUT_PULLUP if the switch is connected to GND

    // Setup LED pins as outputs and initially turn them off
    pinMode(LED0, OUTPUT);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    digitalWrite(LED0, LOW);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);

    Serial.begin(9600);
    Serial1.begin(9600); //Serial for Bluetooth
    aLastState = digitalRead(outputA);
}

void loop() {
    // Check for data from Serial (for testing modes)
    if (Serial.available()) {
        String command = Serial.readStringUntil('\n');
    }

    aState = digitalRead(outputA);
    if (aState != aLastState) {
        if (aState == LOW) {
            // Increment the counter when the encoder reaches a full detent position (click)
            if (digitalRead(outputB) == LOW) {
                if (counter > minValue) {
                    counter--;
                }
            } else {
                if (counter < maxValue) {
                    counter++;
                }
            }
        }
        aLastState = aState;
        lastActivityTime = millis();  // Update the activity time when encoder turns
    }

    // Turn off all LEDs first
    digitalWrite(LED0, LOW);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);

    // Light up the appropriate LED based on the counter value
    switch (counter) {
        case 0:
            digitalWrite(LED0, HIGH);
            break;
        case 1:
            digitalWrite(LED1, HIGH);
            break;
        case 2:
            digitalWrite(LED2, HIGH);
            break;
        case 3:
            digitalWrite(LED3, HIGH);
            break;
    }

    // Check the switch
    switchState = digitalRead(outputC);
    if (switchState == LOW && lastSwitchState == HIGH) {
        switch (counter) {
            case 0:
                Serial.println("OFF");
                Serial1.println("M0");
                break;
            case 1:
                Serial.println("Mode 1");
                Serial1.println("M1");
                break;
            case 2:
                Serial.println("Mode 2");
                Serial1.println("M2");
                break;
            case 3:
                Serial.println("Mode 3");
                Serial1.println("M3");
                break;
        }
        lastActivityTime = millis();  // Update the activity time when switch is pressed
    }
    lastSwitchState = switchState;

    if (millis() - lastActivityTime > TIMEOUT) {
        // Turn off all LEDs due to inactivity
        digitalWrite(LED0, LOW);
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
    }

    delay(10);  // Small delay for debounce
}
