#include <Keypad.h>
#include <LedControl.h>


const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {6, 7, 8, 9};
byte colPins[COLS] = {2, 3, 4, 5};

Keypad keypadObj = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
LedControl lc = LedControl(10, 12, 11, 1); 

unsigned long previousMillisCountdown = 0;
unsigned long previousMillisDisplay = 0;
unsigned long previousMillisChrono = 0;
unsigned long startChronoMillis = 0;
unsigned long chronoMillis = 0;
unsigned long previousSecond = 0;

long csecondsLeft = 0;
int decrement = 1;

bool explosed = false;
bool defused = false;
bool isCountingDown = false;
bool isProgrammingTime = false;
bool isChronoMode = false;
bool isChronoRunning = false;
bool isChronoPaused = false;

String inputKeys = "";
String programmedTime = "";

long hours = 0;
long minutes = 0;
long seconds = 0;
long milliseconds = 0;

char keypadOutput[32] = {0};

byte playSound = A0;
byte a_segment = B01000000;
byte d_segment = B00001000;

void setup() {
  Serial.begin(9600);

  lc.shutdown(0, false);
  lc.setIntensity(0, 10);
  lc.clearDisplay(0);


  pinMode(13, OUTPUT);
  pinMode(A1, OUTPUT);

startUp();
}

void startUp() {

    for (int i = 0; i < 3; ++i) {
        tone(playSound, 1000, 100);
        digitalWrite(13, HIGH);
        delay(80);
        digitalWrite(13, LOW);
        delay(150);
    }

    for (int i = 0; i < 4; ++i) {
        lc.setRow(0, i, d_segment);
        lc.setRow(0, 7 - i, a_segment);
        delay(50);
        lc.clearDisplay(0);
    }

    for (int i = 3; i >= 0; --i) {
        lc.setRow(0, i, a_segment);
        lc.setRow(0, 7 - i, d_segment);
        delay(50);
        lc.clearDisplay(0);
    }
} 

void displayMessage(const char* message) {
  lc.clearDisplay(0);
  for (int i = 0; i < 8; i++) {
    if (message[i] != '\0') {
      setCustomChar(0, 7 - i, message[i]);
    } else {
      lc.setChar(0, 7 - i, ' ', false);
    }
  }
  delay(1000);
  lc.clearDisplay(0);
}

void setCustomChar(int addr, int digit, char value) {
  byte segments;

  switch (value) {
    case 'r': segments = B00000101; break; // Segments for 'r': E and G
    case 'u': segments = B00011100; break; // Segments for 'u': C, D, E, and G
    case 't': segments = B00001111; break; // Segments for 't': F, G, E, and D
    default:
      lc.setChar(addr, digit, value, false);
      return;
  }
  lc.setRow(addr, digit, segments);
}

void updateCountdownDisplay() {
  long remainingTime = csecondsLeft;

  hours = remainingTime / 3600000;
  remainingTime %= 3600000;
  minutes = remainingTime / 60000;
  remainingTime %= 60000;
  seconds = remainingTime / 1000;
  milliseconds = remainingTime % 1000;

  lc.setDigit(0, 7, hours / 10, false);
  lc.setDigit(0, 6, hours % 10, false);
  lc.setDigit(0, 5, minutes / 10, false);
  lc.setDigit(0, 4, minutes % 10, false);
  lc.setDigit(0, 3, seconds / 10, false);
  lc.setDigit(0, 2, seconds % 10, false);
  lc.setDigit(0, 1, milliseconds / 100, false);
  lc.setDigit(0, 0, (milliseconds / 10) % 10, false);
}

void updateChronoDisplay() {
  unsigned long displayMillis = chronoMillis;

  hours = displayMillis / 3600000;
  displayMillis %= 3600000;
  minutes = displayMillis / 60000;
  displayMillis %= 60000;
  seconds = displayMillis / 1000;
  milliseconds = displayMillis % 1000;

  lc.setDigit(0, 7, hours / 10, false);
  lc.setDigit(0, 6, hours % 10, false);
  lc.setDigit(0, 5, minutes / 10, false);
  lc.setDigit(0, 4, minutes % 10, false);
  lc.setDigit(0, 3, seconds / 10, false);
  lc.setDigit(0, 2, seconds % 10, false);
  lc.setDigit(0, 1, milliseconds / 100, false);
  lc.setDigit(0, 0, (milliseconds / 10) % 10, false);
}

void programTime() {
  if (inputKeys.length() == 8) {
    programmedTime = inputKeys;
    Serial.print("Programmed Time: ");
    Serial.println(programmedTime);

    lc.clearDisplay(0);
    inputKeys = "";
  }
}

void startCountdown() {
  Serial.println("Starting Countdown...");

  if (programmedTime.length() == 8) {
    hours = programmedTime.substring(0, 2).toInt();
    minutes = programmedTime.substring(2, 4).toInt();
    seconds = programmedTime.substring(4, 6).toInt();
    milliseconds = programmedTime.substring(6, 8).toInt() * 10;

    csecondsLeft = ((hours * 3600) + (minutes * 60) + seconds) * 1000 + milliseconds;
  } else {
    Serial.println("Invalid programmed time. Please enter a time in HHMMSSCC format.");
    return;
  }

  updateCountdownDisplay();
  isCountingDown = true;
}

void startChrono() {
  isChronoRunning = true;
  isChronoPaused = false;
  startChronoMillis = millis();
}

void pauseChrono() {
  if (isChronoRunning) {
    isChronoPaused = !isChronoPaused;
    if (isChronoPaused) {
      chronoMillis += millis() - startChronoMillis;
    } else {
      startChronoMillis = millis();
    }
  }
}

void resetChrono() {
  isChronoRunning = false;
  isChronoPaused = false;
  chronoMillis = 0;
  lc.clearDisplay(0);
}

void loop() {
  char key = keypadObj.getKey();

  if (key) {
    handleKeypadInput(key);
  }

  if (isCountingDown) {
    handleCountdown();
  }

  if (isChronoRunning && !isChronoPaused) {
    handleChrono();
  }

}

void handleKeypadInput(char key) {
  Serial.print("Key Pressed: ");
  Serial.println(key);

  if ((isCountingDown && decrement == 0) || !isCountingDown) {
    if ((isChronoRunning && isChronoPaused) || !isChronoRunning) {
      if (key == '#') {
        isChronoMode = false;
        lc.clearDisplay(0);
        displayMessage("Count.dn "); // Afficher Countdn pour le mode compte à rebours
        Serial.println("Mode: Countdown");
      } else if (key == '*') {
        isChronoMode = true;
        lc.clearDisplay(0);
        displayMessage("Chrono  "); // Afficher Chrono pour le mode chronomètre
        Serial.println("Mode: Chronometer");
      }
    }
  }

  if (key >= '0' && key <= '9') {
    handleNumericKey(key);
  } else {
    switch (key) {
      case 'A':
        handleKeyA();
        break;
      case 'B':
        handleKeyB();
        break;
      case 'C':
        handleKeyC();
        break;
      case 'D':
        handleKeyD();
        break;
    }
  }
}

void handleNumericKey(char key) {
  if (!isChronoMode && isProgrammingTime) {
    int num = key - '0';
    int displayIndex = inputKeys.length();
    if (displayIndex < 8) {
      lc.setDigit(0, 7 - displayIndex, num, false); // Affichage de droite à gauche sur le deuxième afficheur
      inputKeys += key;
      tone(playSound, 2000, 50);
    }
  }
}

void handleKeyA() {
  if (!isChronoMode) {
    Serial.println("Programming Time...");
    isProgrammingTime = true;
    inputKeys = "";
    programmedTime = "";
    lc.clearDisplay(0);
  }
}

void handleKeyB() {
  if (isChronoMode) {
    pauseChrono();
  } else {
    if (isCountingDown) {
      if (!defused) {
        decrement = 0;
        defused = true;
      }
    }
  }
}

void handleKeyC() {
  if (isChronoMode) {
    resetChrono();
  } else {
    isProgrammingTime = false;
    lc.clearDisplay(0);
  }
}

void handleKeyD() {
  if (isChronoMode) {
    startChrono();
  } else {
    if (isProgrammingTime) {
      isProgrammingTime = false;
      programTime();
      startCountdown();
    } else if (isCountingDown && defused) {
      decrement = 1;
      defused = false;
    }
  }
}

void handleCountdown() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillisCountdown >= 10) {
    previousMillisCountdown = currentMillis;

    if (csecondsLeft > 0 && decrement > 0) {
      csecondsLeft -= 10;

      if (csecondsLeft <= 0) {
        csecondsLeft = 0;
        if (!explosed) {
          Serial.print("! DETONATING !");

          digitalWrite(13, HIGH);
          digitalWrite(A1, HIGH);

          tone(playSound, 1000);
          explosed = true;
        }
      }

      if (csecondsLeft / 1000 != previousSecond) {
        previousSecond = csecondsLeft / 1000;
        tone(playSound, 1000, 100);
      }
      updateCountdownDisplay();
    }
  }
}

void handleChrono() {
  unsigned long currentMillis = millis();
  chronoMillis += currentMillis - startChronoMillis;
  startChronoMillis = currentMillis;
  updateChronoDisplay();
}
