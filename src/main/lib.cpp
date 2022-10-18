#include "lib.h"
#define EI_ARDUINO_INTERRUPTED_PIN
#include "EnableInterrupt.h"

extern bool hasPenality;
extern int state;
extern int leds[];
extern int buttons[];
extern int score;
extern int penalities;
extern int f;
extern int currentIntensity;
extern int fadeAmount;
extern int prevLeds[];
extern int pressButt[];
extern int t2;
extern int t3;
extern int newRound;
extern int newSleep;

int t2;
int t3;
unsigned long prevTime;;

void setInterrupts() {
  for (int i = 0; i < 4; i++) {
    enableInterrupt(buttons[i], check, RISING);
  }
}

void setDifficulty() {
  int L = (analogRead(POT) / 256) + 1; // L is the newDiff and assume values between 1 and 4
  if (f != L * 100) {
    f = L * 100;
  }
}

void turnOffLeds() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(leds[i], LOW);
  }
}

void fadingRed() {
  static unsigned long actualTime = millis();
  if (newRound) {
    actualTime = millis();
    newRound = 0;
  }
  if (millis() - actualTime >= FADE_TIME) {
    actualTime = millis();
    currentIntensity += fadeAmount;
    if (currentIntensity <= 0 || currentIntensity >= 255) {
      fadeAmount = -fadeAmount;
    }
    analogWrite(LR, currentIntensity);
  }
}

void setState(int newState) {
  state = newState;
  newRound = 1;
  if (newSleep != 1) {
    newSleep = 1;
  }
}

bool timer(int waitTime){
  if (newRound) {
    prevTime = millis();
    newRound = 0;
  }
  return millis() - prevTime >= waitTime;
}

void createAndDisplayPattern() {
  int numOn = 0;
  if (timer(T1)) {
    for (int i = 0; i < 4; i++) {
      prevLeds[i] = LOW;
      pressButt[i] = LOW;
      hasPenality = false;
      if (random(0, 2) == 0) {
        digitalWrite(leds[i], HIGH);
        prevLeds[i] = HIGH;
        numOn++;
      }
    }
    if (numOn == 0) { //se tutti i led sono casualmente spenti accendo il primo
      digitalWrite(LG1, HIGH);
    }
    setState(state + 1);
  }
}

void initialState() {
  turnOffLeds();
  fflush(stdout);
  Serial.println("\nWelcome to Catch the Led Pattern Game. Press Key T1 to Start");
  fflush(stdout);
  score = 0;
  penalities = 0;
  hasPenality = false;
  t2 = T2;
  t3 = T3;
  setState(state + 1);

}

void waitForPlayer() {
  if (newSleep) {
    prevTime = millis();
    newSleep = 0;
  }
  if (millis() - prevTime >= PRE_SLEEP_TIME) {
    prevTime = millis();
    digitalWrite(LR, LOW);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode();
    setState(1);
  }
}

void startGame() {
  digitalWrite(LR, LOW);
  Serial.print("You choose difficulty: ");
  Serial.println(f / 100);
  Serial.println("Go!");
  setState(state + 1);
}

void runGame() {
  if (timer(T1)) {
    createAndDisplayPattern();
  }
}

void waitAndHidePattern() {
  if (timer(t2)) {
    for (int i = 0; i < 4; i++) {
      digitalWrite(leds[i], LOW);
    }
    setState(state + 1);
  }
}

void inputFromButton() {
  if (timer(t3)) {
    setState(state + 1);
  }
}

void penality() {
  hasPenality = true;
  penalities++;
  digitalWrite(LR, HIGH);
  for (int i = 0; i < 4; i++) {
    turnOffLeds();
    prevLeds[i] = LOW;
    pressButt[i] = LOW; 
  }
  Serial.print("Penality N.");
  Serial.println(penalities);
  setState(7);
}

void showPoint() {
  turnOffLeds();
  score++;
  Serial.print("New Point! Score: ");
  Serial.println(score);
  setState(3);
  t2 -= f;
  t3 -= f;
}

void checkInputs() {
  for (int i = 0; i < 4; i++) {
    if (pressButt[i] != prevLeds[i]) {
      penality();
      return;
    }
  }
  setState(8);
}

void afterPenality() {
  if (timer(TR)) {
    digitalWrite(LR, LOW);
    if (penalities >= 3) {
      Serial.print("Game Over. Final Score: ");
      Serial.println(score);
      setState(9);
    } else {
      setState(3);
    }
  }
}

void endGame() {
  if (timer(TEG)) {
    setState(0);
  }
}

void check() {
  //gives a penality once for pattern
  if (!hasPenality) {
    //if it's the first state makes the game starts or disable sleepMode
    if (state == 1) {
      if (arduinoInterruptedPin == B1) {
        setState(state + 1);
      }
      sleep_disable();
    } else if (state!=5) {
      //if I press in the wrong state I recive a penality
      penality();
    } else if (state == 5) {
      //collect results from input
      for (int i = 0; i < 4; i++) {
        if (buttons[i] == arduinoInterruptedPin) {
          pressButt[i] = HIGH;
          digitalWrite(leds[i], HIGH);
        }
      }
    }
  }
}
