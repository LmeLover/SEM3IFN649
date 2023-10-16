#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 1

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup(void)
{
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");
  sensors.begin();
  // Setup Serial1 for BlueTooth
  Serial1.begin(9600); // Default communication rate of the Bluetooth module
}

void loop(void)
{
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures();
  Serial.println("DONE");

  float tempC = sensors.getTempCByIndex(0);

  Serial.print("Temperature in cooler is: ");
  Serial.print(tempC);

  Serial1.print("Temperature in cooler is: ");
  Serial1.print(tempC);

  if (tempC < 4.0)
  {
    Serial.println("[Safe]");
    Serial1.println("[Safe]");
    delay(1000);
  }
  else if (tempC >= 4.0 && tempC <= 8.0)
  {
    Serial.println("[Caution]");
    Serial1.println("[Caution]");
    delay(1000);
  }
  else
  {
    Serial.println("[Warning]");
    Serial1.println("[Warning]");
    delay(1000);
  }
}
