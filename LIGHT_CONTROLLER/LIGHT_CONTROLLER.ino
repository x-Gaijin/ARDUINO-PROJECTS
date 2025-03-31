#define LED_KITCHEN 2
#define LED_BEDROOM 3
#define LED_LIVING 4

void setup() {
    Serial.begin(9600); 
    pinMode(LED_KITCHEN, OUTPUT);
    pinMode(LED_BEDROOM, OUTPUT);
    pinMode(LED_LIVING, OUTPUT);
}

void loop() {
    if (Serial.available()) {
        String command = Serial.readStringUntil('\n');
        command.trim(); 

        if (command == "Kitchen ON") digitalWrite(LED_KITCHEN, HIGH);
        if (command == "Kitchen OFF") digitalWrite(LED_KITCHEN, LOW);
        if (command == "Bedroom ON") digitalWrite(LED_BEDROOM, HIGH);
        if (command == "Bedroom OFF") digitalWrite(LED_BEDROOM, LOW);
        if (command == "LivingRoom ON") digitalWrite(LED_LIVING, HIGH);
        if (command == "LivingRoom OFF") digitalWrite(LED_LIVING, LOW);
        
        Serial.println("Status: " + command); 
    }
}
