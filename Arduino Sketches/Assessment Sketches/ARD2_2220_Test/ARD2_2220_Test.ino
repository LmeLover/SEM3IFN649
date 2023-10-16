int Led = 11; // define LED Interface
int buttonpin = 20; // define the tilt switch sensor interfaces
int val; // define numeric variables val

void setup () {
pinMode(Led, OUTPUT); // define LED as output interface
pinMode(buttonpin, INPUT); // define the output interface tilt switch sensor
Serial.begin(9600);}

void loop () {
val = analogRead(buttonpin); // digital interface will be assigned a value of 3 to read val
Serial.println(val);
// When the tilt sensor detects a signal when the switch, LED flashes
if (val == HIGH) {
digitalWrite(Led, HIGH);
Serial.println("Excessive Tilt!");
delay(200);
}
else {
digitalWrite(Led, LOW);
Serial.println("Balanced");
delay(200);
}
}