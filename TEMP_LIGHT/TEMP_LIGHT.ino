#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 9         
#define DHTTYPE DHT11    
#define LDR_PIN A0       
#define BUTTON_PIN 10    

DHT dht(DHTPIN, DHTTYPE);  
LiquidCrystal_I2C lcd(0x27, 16, 2); 

bool displayDHT = true; 
bool lastButtonState = HIGH; 
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 200;  // 200ms debounce time

void setup() {
    Serial.begin(9600);
    dht.begin();
    lcd.init();
    lcd.backlight();
    delay(100);  // Ensure LCD is ready before displaying text

    pinMode(BUTTON_PIN, INPUT_PULLUP); 
}

void loop() {
    checkButtonPress(); 

    if (displayDHT) {
        displayDHTReadings();
    } else {
        displayLDRReadings();
    }

    delay(500); 
}

void checkButtonPress() {
    bool buttonState = digitalRead(BUTTON_PIN);

    if (buttonState == LOW && lastButtonState == HIGH && (millis() - lastDebounceTime > debounceDelay)) {
        displayDHT = !displayDHT; 
        lastDebounceTime = millis();
        lcd.clear();  // Clear only when switching screens
    }

    lastButtonState = buttonState;
}

void displayDHTReadings() {
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    if (isnan(humidity) || isnan(temperature)) {
        Serial.println("DHT11 Error!");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("DHT11 Error!");
    } else {
        Serial.print("Temp: ");
        Serial.print(temperature);
        Serial.print(" C, Humidity: ");
        Serial.print(humidity);
        Serial.println(" %");

        lcd.setCursor(0, 0);
        lcd.print("Temp: ");
        lcd.print(temperature);
        lcd.print(" C  ");  // Extra spaces para matabunan ang lumang text

        lcd.setCursor(0, 1);
        lcd.print("Humidity: ");
        lcd.print(humidity);
        lcd.print(" %  ");  // Extra spaces para matabunan ang lumang text
    }
}

void displayLDRReadings() {
    int lightValue = analogRead(LDR_PIN); 
    float voltage = lightValue * (5.0 / 1023.0);  // Convert to voltage

    Serial.print("Light: ");
    Serial.print(lightValue);
    Serial.print(" | Voltage: ");
    Serial.println(voltage, 2);

    lcd.setCursor(0, 0);
    lcd.print("Light Level:");

    lcd.setCursor(0, 1);
    lcd.print("Val: ");
    lcd.print(lightValue);
    lcd.print(" | ");
    lcd.print(voltage, 2);
    lcd.print("V  ");  // Extra spaces para ma-clear ang previous text
}
