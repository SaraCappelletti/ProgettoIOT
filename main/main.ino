//Authors: Cappelletti Sara, Beleffi Leonardo

#include "lib.h"

bool hasPenality = false;
int state = 0;
int leds[4] = {LG1, LG2, LG3, LG4};
int buttons[4] = {B1, B2, B3, B4};
int score = 0;
int penalities = 0;
int f = 100;
int currentIntensity = 0;
int fadeAmount = 5;
int prevLeds[4] = {LOW, LOW, LOW, LOW};
int pressButt[4] = {LOW, LOW, LOW, LOW};
int newRound = 1;
int newSleep = 1;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 4; i++) {
    pinMode(buttons[i], INPUT);
    pinMode(leds[i], OUTPUT);
  }
  pinMode(LR, OUTPUT);
  randomSeed(analogRead(5));
  setInterrupts();
}

void loop() {
  switch (state) {
    case 0: {
      initialState();
      break;
    }
    case 1: {
      fadingRed();
      setDifficulty();
      waitForPlayer();
      break;
    }
    case 2: {
      startGame();
      break;
    }
    case 3: {
      runGame();
      break;
    }
    case 4: {
      waitAndHidePattern();
      break;
    }
    case 5: {
      inputFromButton();
      break;
    }
    case 6: {
      checkInputs();
      break;
    }
    case 7: {
      afterPenality();
      break;
    }
    case 8: {
      showPoint();
      break;
    }
    case 9: {
      endGame();
      break;
    }
  }
}
