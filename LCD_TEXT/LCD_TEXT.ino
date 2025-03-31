#include <Keypad.h>

const byte numRows = 4;
const byte numCols = 4;

char keys[numRows][numCols] = {
  {'1', '2', '3', ' '},
  {'4', '5', '6', ' '},
  {'7', '8', '9', ' '},
  {'*', '0', '#', ' '}
};

byte rowPins[numRows] = {9, 8, 7, 6};
byte colPins[numCols] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, numRows, numCols);

// Characters for each key
const char keyMap[10][5] = {
  " ",     // 0
  " ",     // 1
  "ABC",   // 2
  "DEF",   // 3
  "GHI",   // 4
  "JKL",   // 5
  "MNO",   // 6
  "PQRS",  // 7
  "TUV",   // 8
  "WXYZ"   // 9
};

char lastKey = '\0';          // To store the last key pressed
unsigned long lastPressTime = 0; // Time when the last key was pressed
uint8_t keyPressCount[10] = {0}; // Track the press count for each key

void setup() {
  Serial.begin(9600);
}

void loop() {
  char key = keypad.getKey();  // Get the key pressed from the keypad

  if (key) {
    unsigned long currentTime = millis();
    uint8_t keyIndex = key - '0';  // Convert char to index (e.g., '2' becomes 2)

    // If the same key is pressed within 700ms, increment the press count
    if (key == lastKey && (currentTime - lastPressTime < 700)) {
      keyPressCount[keyIndex] = (keyPressCount[keyIndex] + 1) % strlen(keyMap[keyIndex]);
    } else {
      // Reset press count for a new key press
      keyPressCount[keyIndex] = 1;
    }

    // Save the time of the last press
    lastPressTime = currentTime;
    lastKey = key;
  }

  // Now check if the time has passed for a complete press cycle (e.g., 1st, 2nd, or 3rd press)
  unsigned long pressCycleTime = 1000;  // Time in ms to accumulate presses before displaying a result

  // Only display after the specified press cycle time has elapsed
  if ((millis() - lastPressTime) > pressCycleTime) {
    if (lastKey != '\0') {
      uint8_t keyIndex = lastKey - '0';  // Convert the last key to an index

      // Ensure the key press count is within the valid range (i.e., 1 to length of the key map)
      if (keyPressCount[keyIndex] > 0 && keyPressCount[keyIndex] <= strlen(keyMap[keyIndex])) {
        // Print the letter corresponding to the current press count
        char outputChar = keyMap[keyIndex][keyPressCount[keyIndex] - 1];
        Serial.print(outputChar);  // Print the corresponding letter to Serial Monitor
      }

      // Reset the press count after displaying the letter
      keyPressCount[keyIndex] = 0;  // Reset the count after each cycle

      // Clear lastKey to avoid printing the same key repeatedly
      lastKey = '\0';
    }
  }
}