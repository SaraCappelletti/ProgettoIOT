#include "lib.h"
#define EI_ARDUINO_INTERRUPTED_PIN
#include "EnableInterrupt.h"

extern int state;
extern int score;
extern int penalities;
extern int buttons[];
extern int currentIntensity;
extern int prevLeds[];
extern int pressButt[];
extern int leds[];
extern int f;
extern int t2;
extern int t3;
extern int fadeAmount;
extern int newRound;
extern int newSleep;
extern bool hasPenality;

int t2;
int t3;

//CHIEDERE a ricci dei quadrati nel serial monitor
//problema di bouncing
//stampa pre sleep mode OPZIONALE

void setInterrupts(){
  for(int i = 0; i < 4; i++){
    enableInterrupt(buttons[i], check, RISING);
  }
}

void setDifficulty(){
  int L = (analogRead(POT) / 256) + 1; // L is the newDiff and assume values between 1 and 4
  if(f != L * 100){
    Serial.println(L);
    f = L * 100;
  }
}

void turnOffLeds() {
  for (int i = 0; i < 4; i++){
    digitalWrite(leds[i], LOW);
  }
}

void fadingRed(int fadeTime){
  static unsigned long actualTime = millis();
  if(newRound){
    actualTime = millis();
    newRound = 0;
  }
  if(millis() - actualTime >= fadeTime){
    actualTime = millis();
    currentIntensity += fadeAmount;
    if(currentIntensity <= 0 || currentIntensity >= 255){
      fadeAmount = -fadeAmount;
    }
    analogWrite(LR, currentIntensity);
  }
}

void setState(int newState){
  state = newState;
  newRound = 1;
  if(newSleep != 1){
    newSleep = 1;
  }
}

void createAndDisplayPattern(){
  static unsigned long waitTime = millis();
  if(newRound){
    waitTime = millis();
    newRound = 0;
  }
  int numOn = 0;
  if(millis() - waitTime >= T1){
    for(int i = 0; i < 4; i++){
      prevLeds[i] = LOW;
      pressButt[i] = LOW;
      hasPenality = false;
      if(random(0, 2) == 0){
        digitalWrite(leds[i], HIGH);
        prevLeds[i] = HIGH;
        numOn++;
      }
    }
    if(numOn == 0){ //se tutti i led sono casualmente spenti accendo il primo
      digitalWrite(LG1, HIGH);
    }
    setState(state + 1);
  }
}

void initialState(){
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

void waitForPlayer(int preSleepTime){
  static unsigned long waitTime = millis();
  if(newSleep){
    waitTime = millis();
    newSleep = 0;
  }
  if(millis() - waitTime >= preSleepTime){
    //Serial.println("Entering sleep mode");
    waitTime = millis();
    digitalWrite(LR, LOW);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode();
    setState(1);
  }
}

void startGame(){
  digitalWrite(LR, LOW);
  Serial.print("You choose difficulty: ");
  Serial.println(f / 100);
  Serial.println("Go!");
  setState(state + 1);
}

void runGame(){
  static unsigned long waitTime = millis();
  if(newRound){
    waitTime = millis();
    newRound = 0;
  }
  if(millis() - waitTime >= T1){
    createAndDisplayPattern();
  }
}

void waitAndHidePattern(){
  static unsigned long waitTime = millis();
  if(newRound){
    waitTime = millis();
    newRound = 0;
  }
  if(millis() - waitTime >= t2){
    for(int i = 0; i < 4; i++){
      digitalWrite(leds[i], LOW);
    }
    setState(state + 1);
  }
}

void inputFromButton(){
  static unsigned long waitTime = millis();
  if(newRound){
    waitTime = millis();
    newRound = 0;
  }
  if(millis() - waitTime >= t3){
    setState(state + 1);
  }
}

void penality(){
  hasPenality = true;
  penalities++;
  digitalWrite(LR, HIGH);
  for(int i = 0; i < 4; i++) {
    turnOffLeds();
    prevLeds[i] = LOW;
    pressButt[i] = LOW; 
  }
  Serial.print("Penality N.");
  Serial.println(penalities);
  delayMicroseconds(1000000);
  digitalWrite(LR, LOW);
  if(penalities >= 3){
    setState(8);
  } else {
    setState(3);
  }
}

void showPoint(){
  turnOffLeds();
  score ++;
  Serial.print("New Point! Score: ");
  Serial.println(score);
  setState(3);
  t2 -= f;
  t3 -= f;
}

void checkInputs(){
  for(int i = 0; i < 4; i++){
    if(pressButt[i] != prevLeds[i]){
      penality();
      return;
    }
  }
  setState(state + 1);
}

void endGame(){
  static unsigned long waitTime = micros();
  Serial.print("Game Over. Final Score: ");
  Serial.println(score);
  if(newRound){
    waitTime = micros();
    newRound = 0;
  }
  Serial.println(micros()-waitTime);
  if(micros() - waitTime >= 5000000){
    setState(0);
  }
}

void check(){
  if (!hasPenality) {
    if(state == 1){ //starting game
      if(arduinoInterruptedPin == B1){
        setState(state + 1);
      }
      sleep_disable();
      //return;
    }
    else if(state!=5){
      penality();
    }
    else if(state == 5){ //collect results
      for(int i = 0; i < 4; i++){
        if(buttons[i] == arduinoInterruptedPin){
          pressButt[i] = HIGH;
          digitalWrite(leds[i], HIGH);
        }
      }
    }
    /*else {
      penality();
    }*/
  }
}


