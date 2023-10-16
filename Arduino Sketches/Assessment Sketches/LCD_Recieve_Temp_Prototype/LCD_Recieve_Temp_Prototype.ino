#include <Wire.h>
#include <hd44780.h>                // main hd44780 header
#include <hd44780ioClass/hd44780_I2Cexp.h> // i2c expander i/o class header

hd44780_I2Cexp lcd; // declare lcd object: auto locate & auto config expander chip

void setup()
{
   int status;

   // Set up LCD for 16 columns and 1 row
   status = lcd.begin(16, 1);
   if(status) // non zero status means it was unsuccessful
   {
      hd44780::fatalError(status); // does not return
   }

   // Set up Serial1 for Bluetooth
   Serial1.begin(9600);

   lcd.print("Temp: Waiting...");
}

void loop()
{
   if(Serial1.available())  // if data is available to read
   {
      String tempString = Serial1.readString(); // read it into a string

      lcd.clear(); // Clear the display
      lcd.print(tempString);  // Display the temperature string received from Bluetooth  // degree symbol
      delay(1000);
   }
}
