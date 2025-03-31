#define button 10
#define switch1 11
#define switch2 12

int state = 0;
int old = 0;
int current = 0;

void setup() {
  for (int i = 2; i < 10; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(button, INPUT);
  pinMode(switch1, INPUT);
  pinMode(switch2, INPUT);
}

void loop() {
  current = digitalRead(button);
  if (current == 1) {
    delay(50); 
    while (digitalRead(button) == 1); 
    state = old + 1; 
    old = state; 
  }

  switch (state) {
    case 1:
      for (int i = 2; i < 10; i++) {
        digitalWrite(i, HIGH);
      }
      break;

    case 2:
      for (int i = 2; i < 10; i++) {
        digitalWrite(i, HIGH);
      }
      delay(100);
      for (int i = 2; i < 10; i++) {
        digitalWrite(i, LOW);
      }
      delay(100);
      break;

    case 3:
       for(int i = 2; i < 10; i++) {
      digitalWrite(i, (i % 2 == 0)? HIGH : LOW);
    }
    delay(100);
    for(int i = 2; i < 10; i++) {
      digitalWrite(i, (i % 2 == 0)? LOW : HIGH);
    }
    delay(100);
    break;
    case 4:
     for(int i=2;i<=10;i++)
  {
    int a=10-(i-2);
    digitalWrite(i,HIGH);
    digitalWrite(a,HIGH);
    delay(100);
    digitalWrite(i,LOW);
    digitalWrite(a,LOW);
  }
  break;

  case 5:
   for(int i=2;i<=10;i++)
  {
    digitalWrite(i,HIGH);
  
    delay(100);
    digitalWrite(i,LOW);

  }
  break;

  case 6:
  if (digitalRead(switch1)) {
      if (digitalRead(switch2)) {
      for(int i = 2; i < 10; i++) {
        digitalWrite(i, LOW);
      }
    }
    else {
      for(int i = 2; i < 6; i++) {
        digitalWrite(i, LOW);
      }
      for(int i = 6; i < 10; i++) {
        digitalWrite(i, HIGH);
      }
    }
  }
  else {
    if (digitalRead(switch2)) {
      for(int i = 2; i < 6; i++) {
        digitalWrite(i, HIGH);
      }
      for(int i = 6; i < 10; i++) {
        digitalWrite(i, LOW);
      }
    }
    else {
      for(int i = 2; i < 10; i++) {
        digitalWrite(i, HIGH);
      }
    }
  }
  break;


    default:
      for (int i = 2; i < 10; i++) {
        digitalWrite(i, LOW);
      }
      state = 0; 
      old = 0;
      break;
  }
}