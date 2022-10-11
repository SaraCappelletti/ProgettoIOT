#ifndef __LIB_H__
#define __LIB_H__

#include <arduino.h>
#include <avr/sleep.h>

#define B1 4
#define B2 5
#define B3 6
#define B4 7
#define LR 9
#define LG4 10
#define LG3 11
#define LG2 12
#define LG1 13
#define POT A0
#define T1 2000



void turnOffLeds(int leds[]);

void fadingRed(int fadeTime, int fadeAmount);

void changeState();

void checkPressedButtons(int pressed[]);

void createAndDisplayPatterns();

void initialState(int leds[]);

void waitForPlayer(int preSleepTime);

void startGame();

void runGame();

void showPattern();

void inputFromButton();

void penality();

void checkInputs();

void check();

#endif
