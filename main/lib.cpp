#include "lib.h"

extern int state;
extern int penalities;
extern int buttons[];
extern int currentIntensity;
extern int prevLeds[];

void turnOffLeds(int leds[]) {
  for (int i = 0; i < 4; i++){
    digitalWrite(leds[i], LOW);
  }
}

void fadingRed(int fadeTime, int fadeAmount){
  static unsigned long actualTime = micros();
  if(micros() - actualTime >= fadeTime){
    actualTime = micros();
    currentIntensity += fadeAmount;
    analogWrite(LR, currentIntensity + fadeAmount);
    if (currentIntensity == 0 || currentIntensity == 255){
      fadeAmount = -fadeAmount;
    }
  }

}

void changeState(){
  state = (state + 1) % 4;
}

void checkPressedButtons(int pressed[]){
  for(int i = 0; i < 4; i++){
    if(digitalRead(buttons[i])){
      pressed[i] = HIGH;
    }
    else{
      pressed[i] = LOW;
    }
  }
}

void createAndDisplayPatterns(){
  for(int i = 0; i < 4; i++){
    if(random(0, 2) == 0){
      digitalWrite(leds[i], HIGH);
      prevleds[i] = HIGH;
    }
  }
}

void initialState(int leds[]){
  turnOffLeds(leds);
  Serial.println("Welcome to Catch the Led Pattern Game. Press Key T1 to Start");
}

void waitForPlayer(int preSleepTime){
  static unsigned long waitTime = micros();
  if(micros() - waitTime >= preSleepTime){
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode(); //controlla
  }
}

void startGame(){
  digitalWrite(LR, LOW);
  Serial.println("Go!");
  changeState();
}

void runGame(){
  static unsigned long waitTime = micros();
  if(micros() - waitTime >= t1){
    createAndDisplayPattern();
    changeState();
  }
}

void showPattern(){
  static unsigned long waitTime = micros();
  if(micros() - waitTime >= t2){
    for(int i = 0; i < 4; i++){
      digitalWrite(leds[i], LOW);
    }
    chageState();
  }
}

void inputFromButton(){
  static unsigned long waitTime = micros();
  if(micros() - waitTime >= t3){
    for(int i = 0; i < 4; i++){
      digitalWrite(leds[i], LOW);
    }
    chageState();
  }
}

void penality(){
  penalities++;
  digitalWrite(LR, HIGH);
  Serial.println("Penality!");
  delay(1000);
  digitalWrite(LR, LOW);
}

void checkInputs(){
  for(int i = 0; i < 4; i++){
    if(pressbutt[i] != prevleds[i]){
      penality();
    }
  }
}

void check(){
  int pressed[4];
  checkPressedButtons(pressed);
  if(state == 1){ //starting game
    if(pressed[0] == HIGH){
      changeState();
    }
    sleep_disable();
  }
  if(state == 5){ //collect results
    for(int i = 0; i < 4; i++){
     digitalWrite(leds[pressed], HIGH);
    }
  }
  else {
    penality();
  }
}


