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
int preSleepTime = 5000;
int fadeTime = 20;
int fadeAmount = 5;
int currentIntensity = 0;
unsigned long time = 0;
int prevLeds[4] = {LOW, LOW, LOW, LOW};
int pressButt[4] = {LOW, LOW, LOW, LOW};

int newRound = 1;
int newSleep = 1;

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
  randomSeed(analogRead(5));
  setInterrupts();
}

void loop() {
  switch (state) {
    case 0:{
/*
      Serial.println("LEDS ");
      for (int i = 0; i < 4; i++)
        Serial.println(leds[i]);
      
      Serial.println("BUTTONS ");
      for (int i = 0; i < 4; i++)
        Serial.println(buttons[i]);

      Serial.print("SCORE ");
      Serial.println(score);

      Serial.print("PENALITIES ");
      Serial.println(penalities);

      Serial.println("PREV_LEDS ");
      for (int i = 0; i < 4; i++)
        Serial.println(prevLeds[i]);

      Serial.println("PRESSED_BUTTS ");
      for (int i = 0; i < 4; i++)
        Serial.println(pressButt[i]);
*/
      initialState();
      break;
    }
    case 1:{
      fadingRed(fadeTime);
      waitForPlayer(preSleepTime);
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
      waitAndHidePattern();
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
    case 7:{
      showPoint();
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
