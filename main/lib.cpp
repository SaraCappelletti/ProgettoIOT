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

void setInterrupts(){
  for(int i = 0; i < 4; i++){
    enableInterrupt(buttons[i], check, RISING);
  }
}

void turnOffLeds() {
  for (int i = 0; i < 4; i++){
    digitalWrite(leds[i], LOW);
  }
}

void fadingRed(int fadeTime){  //VA
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

void nextState(){
  state = (state + 1) % 8;
  //Serial.println(state);
  newRound = 1;
}

/*void checkPressedButtons(int pressed[]){
  for(int i = 0; i < 4; i++){
    if(digitalRead(buttons[i])){
      pressed[i] = HIGH;
    }
    else{
      pressed[i] = LOW;
    }
  }
}*/

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
      if(random(0, 2) == 0){
        digitalWrite(leds[i], HIGH);
        prevLeds[i] = HIGH;
        numOn++;
      }
    }
    if(numOn == 0){ //se tutti i led sono casualmente spenti accendo il primo
      digitalWrite(LG1, HIGH);
    }
    nextState();
  }
}

void initialState(){
  turnOffLeds();
  fflush(stdout);
  Serial.println("\nWelcome to Catch the Led Pattern Game. Press Key T1 to Start");
  fflush(stdout);
  newRound = 1;
  score = 0;
  penalities = 0;
  nextState();

}

void waitForPlayer(int preSleepTime){
  static unsigned long waitTime = millis();
  if(newSleep){
    waitTime = millis();
    newSleep = 0;
  }
  if(millis() - waitTime >= preSleepTime){
    waitTime = millis();
    digitalWrite(LR, LOW);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode();
    state = 1;
    newRound = 1;
    newSleep = 1;
    //waitTime = millis();
  }
}

void startGame(){
  digitalWrite(LR, LOW);
  Serial.println("Go!");
  nextState();
}

void runGame(){
  static unsigned long waitTime = millis();
  if(newRound){
    waitTime = millis();
    newRound = 0;
  }
  if(millis() - waitTime >= T1){
    //newRound = 1;
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
    nextState();
  }
}

void inputFromButton(){
  static unsigned long waitTime = millis();
  if(newRound){
    waitTime = millis();
    newRound = 0;
  }
  if(millis() - waitTime >= t3){
    nextState();
  }
}

void penality(){
  penalities++;
  digitalWrite(LR, HIGH);
  for(int i = 0; i < 4; i++) {
    turnOffLeds();
    prevLeds[i] = LOW;
    pressButt[i] = LOW; 
  }
  Serial.println("Penality!");
  delay(1000);
  digitalWrite(LR, LOW);
  if(penalities >= 3){
    endGame();
  } else {
    //Serial.println("prova");
    state = 3;
    newRound = 1;
  }
}

void showPoint(){
  turnOffLeds();
  score ++;
  Serial.print("New Point! Score: ");
  Serial.println(score);
  state = 3;
  newRound = 1;
  t2 -= f;
  t3 -= f;
}

void checkInputs(){
  for(int i = 0; i < 4; i++){
    if(pressButt[i] != prevLeds[i]){
      //Serial.println(pressButt[i]);
      //Serial.println(prevLeds[i]);
      penality();
      return;
    }
  }
  nextState();
}

void endGame(){
  Serial.print("Game Over. Final Score: ");
  Serial.println(score);
  state = 0;
}

void check(){
  //int pressed[4];
  //checkPressedButtons(pressed);
  /*Serial.println("-------------------------------------------------------------");
  Serial.print("State ");Serial.println(state);
  Serial.print("B1 ");Serial.println(digitalRead(B1));
  Serial.print("B2 ");Serial.println(digitalRead(B2));
  Serial.print("B3 ");Serial.println(digitalRead(B3));
  Serial.print("B4 ");Serial.println(digitalRead(B4));*/
  if(state == 1){ //starting game
    if(arduinoInterruptedPin == B1){
      nextState();
    }
    sleep_disable();
    //return;
  }
  else if(state == 5){ //collect results
    for(int i = 0; i < 4; i++){
      if(buttons[i] == arduinoInterruptedPin){
        pressButt[i] = HIGH;
        digitalWrite(leds[i], HIGH);
      }
    }
  }
  else {
    penality();
    delay(50);
  }
  //Serial.println("-------------------------------------------------------------");
}


