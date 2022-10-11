#include "lib.h"

int state = 0; //0 beforegame, 1 gamestart, 2 insertion, 3 control
int leds[4] = {LG1, LG2, LG3, LG4};
int buttons[4] = {B1, B2, B3, B4};
int score = 0;
int penalities = 0;
int t2 = 3000;
int t3 = 3000;
int tr = 1000;
int f = 250;
int preSleepTime = 10000;
int fadeTime = 20000;
int fadeAmount = 5;
int currentIntensity = 0;
unsigned long time = 0;
int prevleds[4] = {LOW, LOW, LOW, LOW};
int pressbutt[4] = {LOW, LOW, LOW, LOW};

void setup() {
  Serial.begin(9600);
  pinMode(B1, INPUT);
  pinMode(B2, INPUT);
  pinMode(B3, INPUT);
  pinMode(B4, INPUT);
  pinMode(LG1, OUTPUT);
  pinMode(LG2, OUTPUT);
  pinMode(LG3, OUTPUT);
  pinMode(LG4, OUTPUT);
  pinMode(LR, OUTPUT);
  randomSeed(analogRead(0));
  attachInterrupt(digitalPinToInterrupt(B1), check, RISING);
  attachInterrupt(digitalPinToInterrupt(B2), check, RISING);
  attachInterrupt(digitalPinToInterrupt(B3), check, RISING);
  attachInterrupt(digitalPinToInterrupt(B4), check, RISING);
}

void loop() {
  switch (state) {
    case 0:{
      initialState(leds);
      changeState();
      break;
    }
    case 1:{
      waitForPlayer(preSleepTime);
      fadingRed(fadeTime, fadeAmount);
      break;
    }
    case 2:{
      startGame();
      break;
    }
    case 3:{
      runGame();
      break;
    }
    case 4:{
      showPattern();
      break;
    }
    case 5:{
      inputFromButton();
      break;
    }
    case 6:{
      checkInputs();
      break;
    }
  }



  
  /*if(state == 1){
    turnOffLeds(leds);
    digitalWrite(LR, LOW);

    for(int i = 0; i < 4; i++){
      if(random(0, 2) == 0){
        digitalWrite(leds[i], HIGH);
        prevleds[i] = HIGH;
      }
    }
    state = 1;
    time = millis();
  }
  //stato = inserimento pattern
  if(state == 1 && millis() - time >= t2){
    //turnOffLeds(leds);
    for (int i = 0; i < 4; i++){
      digitalWrite(leds[i], LOW);
    }
    state = 2;
    time = millis();
  }

  if(state == 2 && millis() - time >= t3){
    //turnOffLeds(leds);
    for (int i = 0; i < 4; i++){
      if(prevleds[i] != digitalRead(buttons[i])){
        penalities++;
      }
    }
    if(penalities){
      digitalWrite(LR, HIGH);
      Serial.println("Penality!");
      time = millis();
    }
  }*/
}
