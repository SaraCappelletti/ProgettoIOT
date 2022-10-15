#ifndef __LIB_H__
#define __LIB_H__

#include <arduino.h>
#include <avr/sleep.h>

#define B1 4
#define B2 5
#define B3 6
#define B4 7
#define LR 9
#define LG1 10
#define LG2 11
#define LG3 12
#define LG4 13
#define POT A0
#define T1 2000
#define T2 3000
#define T3 3000

void setInterrupts();

void setDifficulty();

void turnOffLeds();

void fadingRed(int fadeTime);

void setState(int newState);

void checkPressedButtons(int pressed[]);

void createAndDisplayPattern();

void initialState();

void waitForPlayer(int preSleepTime);

void startGame();

void runGame();

void waitAndHidePattern();

void inputFromButton();

void penality();

void showPoint();

void checkInputs();

void endGame();

void check();

#endif
