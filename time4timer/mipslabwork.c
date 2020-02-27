/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2020-02-25 by Ludvig Larsson and Cheehoe Oh 

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */
#include <stdlib.h>
void *stdin, *stdout, *stderr; // Detta behövs för att använda standard biblioteken!

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  TMR2 = 0;                           // reset timer 2
  PR2 = (80000000 / 256) / 10;        // count in prescale (still 1s period) and also divide by 10 for 100ms (fits 16 bit)
  T2CONSET = 0x8070;                  // start timer and set prescaling to 256 (1)000 0000 0(111) 0000 --> 8070

  TMR3 = 0;                           // reset timer 3
  PR3 = (80000000 / 256) / 111;       // to obtain different seeds for the random generator

  IECSET(0) = 0x100;                  // enable interrupt for timer 2

  TRISFSET = 0x1;                     // set button 1 to input
  TRISDSET = 0x7F;                    // set button 2-4 and switch 1-4 to inputs
  
  srand(TMR3);                        // give random generator seeds from TMR3
}

int gameActive = 0;
int userAnswering = 0;
int timeoutcount = 0;
void labwork(void)
{
  if (gameActive == 0)
  {
    startScreen();
  }
  
  if (gameActive == 1)
  {
    if(IFS(0) & 0x100)                // time remaining is displayed
    {
      timeoutcount++;
      IFSCLR(0) = 0x100;
      if (timeoutcount == 10)
      {
        display_string(3, "testing");
        display_update();
      }
      if (timeoutcount == 20)
      {
        display_string(3, "");
        display_update();
        timeoutcount = 0;
        //tick
        //char bottomRow = *score and time*
        //display_update(3, bottomRow)
      }
    }
    if (userAnswering == 0)
    {
      create_question();
      userAnswering = 1;
    }

    if (getbtns() == (0x1 || 0x2))
    {
      userAnswering = 0;
    }
    
    // char test[31];
    // sprintf(test, "%d", TMR2);
  }
}

// void buttonPressed() {

// }

void display_clr()
{
  display_string(0, "");
  display_string(1, "");
  display_string(2, "");
  display_string(3, "");
  display_update();
}

void startScreen()
{
  display_string(0, "Quiz Game");
  display_string(1, "BTN1 to begin");
  display_string(3, "Gametime: 60 sec");
  display_update();
  int btns = getbtns();
    
  if(btns == 0x1)
  {
    display_clr();
    gameActive = 1;
  }
}

