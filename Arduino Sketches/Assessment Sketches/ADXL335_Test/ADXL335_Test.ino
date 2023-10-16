const int xpin = 20;                  // x-axis of the accelerometer

const int ypin = 19;                  // y-axis

const int zpin = 18;                  // z-axis (only on 3-axis models)

void setup() {

  // initialize the serial communications:

  Serial.begin(9600);

  // Provide ground and power by using the analog inputs as normal digital pins.

  // This makes it possible to directly connect the breakout board to the

  // Arduino. If you use the normal 5V and GND pins on the Arduino,

  // you can remove these lines.
}

void loop() {
  // Read the sensor values:
  int xValue = analogRead(xpin);
  int yValue = analogRead(ypin);
  int zValue = analogRead(zpin);

  // Check if any of the values exceed 200:
  if (xValue > 3000 || yValue > 3000 || zValue > 3000) {
    Serial.println("Warning: Excessive movement!");
  } else {
    // If the values are within the acceptable range, print them as usual:
    Serial.print(xValue);
    Serial.print("\t");
    Serial.print(yValue);
    Serial.print("\t");
    Serial.print(zValue);
    Serial.println();
  }

  // Delay before next reading:
  delay(100);
}
