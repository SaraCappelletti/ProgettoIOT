#ifndef __LIB_H__
#define __LIB_H__

#include <arduino.h>
#include <avr/sleep.h>

//button pins
#define B1 4
#define B2 5
#define B3 6
#define B4 7
//red led pin
#define LR 9
//green led pins
#define LG1 10
#define LG2 11
#define LG3 12
#define LG4 13
//potentiometer pin
#define POT A0
//wait time before turn on the sequence
#define T1 2000
//wait time before turn off the sequence
#define T2 3000
//time during wich the player can recreate the sequnce
#define T3 3000 
//wait time before turn off red penalities led
#define TR 1000
//wait time before end the game
#define TEG 10000 
//wait time before change the intensity of the led in fading
#define FADE_TIME 20
//wait time before entering sleep mode
#define PRE_SLEEP_TIME 10000

/*Set all the interrupts in the buttons*/
void setInterrupts();

/*Set the difficulty level with potentiometer*/
void setDifficulty();

/*Turn off all the green leds*/
void turnOffLeds();

/*Make the red led fade*/
void fadingRed();

/*Set the state of the game to the newState value*/
void setState(int newState);

/*Return true if waitTime is passed*/
bool timer(int waitTime);

/*Create a new random sequence of leds, fills up prevLeds and turn the new sequence on*/
void createAndDisplayPattern();

/*Print the Welcome line and set all the variable of the game*/
void initialState();

/*If there is no input before PRE_SLEEP_TIME Arduino enter in sleep mode*/
void waitForPlayer();

/*Show the difficulty and make the game start*/
void startGame();

/*Wait T1 and the call createAndDisplayPattern()*/
void runGame();

/*Wait t2 showing the pattern and then turn the pattern off*/
void waitAndHidePattern();

/*Wait t3 where payer can press the buttons*/
void inputFromButton();

/*Give a penality, turn on the red led and turn off al the other leds*/
void penality();

/*Print the new score and changes t2 and t3*/
void showPoint();

/*Check if the input sequnce is right, if not calls penalities(), otherwise calls showPoints()*/
void checkInputs();

/*Wait TR before turn off the red penality led, if penalities >= 3 calls endGame(), otherwise calls runGame()*/
void afterPenality();

/*Wait TEG before calling runGame()*/
void endGame();

/*Interrupt rutine*/
void check();

#endif
