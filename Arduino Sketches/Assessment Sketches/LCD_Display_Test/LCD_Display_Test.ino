#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize the LiquidCrystal_I2C library with the I2C address (commonly 0x27 or 0x3F) 
// and LCD size (e.g., 16x2)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();  // Initialize the LCD
  lcd.backlight();  // Turn on the backlight
  
  lcd.setCursor(0, 0);  // Set cursor to the top-left corner
  lcd.print("Hello, HD44780!");  // Print a message on the first line
  
  lcd.setCursor(0, 1);  // Set cursor to the start of the second line
  lcd.print("Using I2C");  // Print a message on the second line
}

void loop() {
  // Empty loop for this static display example.
}
