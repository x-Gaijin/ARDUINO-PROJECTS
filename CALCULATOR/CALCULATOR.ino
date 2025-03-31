#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x27, 8, 2);

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','/'},
  {'4','5','6','-'},
  {'7','8','9','+'},
  {'*','0','.','='} // Adjusted bottom-left to '*' and bottom-right to '='
};

byte rowPins[ROWS] = {9,8,7,6}; // Adjusted to match your wiring
byte colPins[COLS] = {5,4,3,2}; // Adjusted to match your wiring

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const int clearButtonPin = 10;

String inputString = "0";
char operatorUsed = '\0';
float num1 = 0, num2 = 0;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.print("CPE Calculator");
  delay(4000);
  lcd.clear();
  lcd.print("0");
  pinMode(clearButtonPin, INPUT_PULLUP); // Use internal pull-up resistor
}

void loop() {
  char key = keypad.getKey();
  int clearButtonState = digitalRead(clearButtonPin);

  if (key) {
    // NUMERAL INPUT
    if (key >= '0' && key <= '9') {
      if (inputString == "0" || inputString == "-0") {
        inputString = (inputString == "-0") ? "-" + String(key) : String(key);
        lcd.clear();
      } else {
        inputString += key;
      }
      lcd.print(key);
    }
    
    // DECIMAL POINT
    else if (key == '.') {
      if (inputString.indexOf('.') == -1) {
        if (inputString.length() == 0 || inputString == "-") inputString += "0.";
        else inputString += '.';
        lcd.print(".");
      }
    }
    
    // OPERATOR HANDLING
    else if (key == '+' || key == '-' || key == '*' || key == '/') {
      if (inputString.length() > 0 && inputString != "-") {
        num1 = inputString.toFloat();
        operatorUsed = key;
        lcd.print(key);
        inputString = "";
      }
      else if (operatorUsed != '\0') {
        if (key == '-' && inputString.length() == 0) {  // Allow negative second number
          inputString = "-";
          lcd.print("-");
        }
        else if (inputString == "-") {
          operatorUsed = key;
          lcd.clear();
          lcd.print(num1);
          lcd.print(operatorUsed);
          inputString = "";
        }
        else {
          operatorUsed = key;
          lcd.clear();
          lcd.print(num1);
          lcd.print(operatorUsed);
        }
      }
    }
    
    // EQUAL BUTTON HANDLING
    else if (key == '=') {
      if (inputString.length() > 0 && operatorUsed != '\0' && inputString != "-") {
        num2 = inputString.toFloat();
        float result = 0;
       
        if (operatorUsed == '/') {
          if (num2 == 0) {
            if (num1 == 0) {
              lcd.clear();
              lcd.print("Indeterminate");
            } else {
              lcd.clear();
              lcd.print("Undefined");
            }
            delay(2000);
            resetCalculator();
            return;
          } else {
            result = num1 / num2;
          }
        } else {
          switch (operatorUsed) {
            case '+': result = num1 + num2; break;
            case '-': result = num1 - num2; break;
            case '*': result = num1 * num2; break;
          }
        }
  
        lcd.clear();
        lcd.print(result);
        inputString = String(result);
        operatorUsed = '\0';
        delay(200);
      }
    }
  }

  // CLEAR BUTTON (Check if pressed)
  if (clearButtonState == LOW) {
    delay(50); // Debounce delay
    resetCalculator();
  }
}

void resetCalculator() {
  lcd.clear();
  inputString = "0";
  operatorUsed = '\0';
  num1 = 0;
  lcd.print("0");
}