#include <Wire.h>
#include <hd44780.h>                // main hd44780 header
#include <hd44780ioClass/hd44780_I2Cexp.h> // i2c expander i/o class header

hd44780_I2Cexp lcd; // declare lcd object: auto locate & auto config expander chip

void setup()
{
   int status;

   // Set up for 16 columns and 1 row
   status = lcd.begin(16, 1);
   if(status) // non zero status means it was unsuccessful
   {
      hd44780::fatalError(status); // does not return
   }
   lcd.print("Temp:");
   lcd.print("25");
   lcd.write((byte)0xDF); // degree symbol
   lcd.print("C");
}

void loop()
{
   // Your loop content here
}
