#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD address 0x27 for 16x2 display
const int buttonPin = 2; // Button connected to pin 2
int messageIndex = 0;    // Keeps track of the current message

void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(buttonPin, INPUT_PULLUP); // Enable internal pull-up resistor

  // Show "Hello World" on startup
  lcd.setCursor(0, 0);
  lcd.print("Hello World ");
  lcd.setCursor(1, 1);
  lcd.print("   Arduino <3");
  delay(2000); // Keep it visible for 2 seconds
}

void loop() {
  // Wait until button is pressed
  while (digitalRead(buttonPin) == HIGH); // Stay here until button is pressed

  delay(200); // Debounce delay
  messageIndex = (messageIndex + 1) % 4; // Cycle through messages
  displayMessage(); // Show the new message

  // Wait until the button is released
  while (digitalRead(buttonPin) == LOW); // Stay here until button is released
}

void displayMessage() {
  lcd.clear(); // Clear the display before showing new text
  lcd.setCursor(0, 0);

  switch (messageIndex) {
    case 0:
      lcd.print("Hello World ");
      lcd.setCursor(1, 1);
      lcd.print("   Arduino <3");
      break;
      
    case 1:
      lcd.print("Tristhan Cabrera");
      lcd.setCursor(2, 1);
      lcd.print("    CPE3A");
      break;
      
    case 2:
      lcd.print("Buti pa ang ");
      lcd.setCursor(0, 1);
      lcd.print("SAGING may PUSO");
      break;
      
    case 3:
      lcd.print("Walang forever...");
      lcd.setCursor(0, 1);
      lcd.print("Pero may Arduino!");
      break;
  }
}

