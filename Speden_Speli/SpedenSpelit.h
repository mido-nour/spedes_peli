#ifndef SPEDENSPELIT_H
#define SPEDENSPELIT_H
#include <arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

// Use these 2 volatile variables for communicating between
// loop() function and interrupt handlers
volatile bool newTimerInterrupt = false;  // for timer interrupt handler
volatile int nappiNumber = -2;            // tämä muuttuja käsittelee numeron jolta nappi isr tulee
volatile int nappiJono = 0;               // napin järjestys
const int buzzer = A0;                    // äänen output pinni
volatile int *randomArray = new int[100]; // taulukko missä säilytetään randomNumerot
volatile int *userArray = new int[100];   // taulukko missä säilytetään userNumerot
volatile int jono = 0;                    // muuttuja random ja user numeroiden määräämän paikan löytämiseen taulukossa
volatile float nopeus = 62499;            // timerin commpare registerin suuruus, jolla timerin keskeytyksen aika määrätään
volatile byte tulos = 0;                  // displayn arvo muuttuja
volatile bool timerStopBool = 1;          // tällä muuttujalla säädellään juokseeko timer vai ei
volatile bool nappiBool = false;          // tällä muuttujalla käsitellään napin ISR keskeytys
volatile int randomMuuttuja = 0;          // tähän muuttujaan tallennetaan random funktion arpoma numero

/*
  initializeTimer() subroutine intializes Arduino Timer1 module to
  give interrupts at rate 1Hz
  
*/
void initializeTimer(void);

// Intoduce TIMER1_COMPA_vect Interrupt Service (ISR) function for timer.
ISR(TIMER1_COMPA_vect);

/*
  initializeGame() subroutine is used to initialize all variables
  needed to store random numbers and player button push data.
  This function is called from startTheGame() function.
  
*/
int initializeGame(void);

/*
  checkGame() subroutine is used to check the status
  of the Game after each player button press.
  
  If the latest player button press is wrong, the game stops
  and if the latest press was right, game display is incremented
  by 1.
  
  Parameters
  byte lastButtonPress of the player 0 or 1 or 2 or 3
  
*/
void checkGame(byte);

/*
  startTheGame() subroutine calls InitializeGame()
  function and enables Timer1 interrupts to start
  the Game.
*/
void startTheGame(void);

// tämä pysäyttää timerin
void stopTheGame(void);

#endif