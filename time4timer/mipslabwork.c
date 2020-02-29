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
void user_isr (void)
{
  return;
}

/* Lab-specific initialization goes here */
void labinit (void)
{
  TMR2 = 0;                           // reset timer 2
  PR2 = (80000000 / 256) / 10;        // count in prescale (still 1s period) and also divide by 10 for 100ms (fits 16 bit)
  T2CONSET = 0x8070;                  // start timer and set prescaling to 256 (1)000 0000 0(111) 0000 --> 8070

  TMR3 = 0;                           // reset timer 3
  PR3 = (80000000 / 256) / 111;       // to obtain different seeds for the random generator

  IECSET(0) = 0x100;                  // enable interrupt for timer 2

  TRISFSET = 0x1;                     // set button 1 to input
  TRISDSET = 0x7F;                    // set button 2-4 and switch 1-4 to inputs
  
  srand(TMR3 ^ TMR2);                 // give random generator seeds from TMR3
}

int gameActive = 0;
int userAnswering = 0;
int timeoutcount = 10;
int timeout = 0;
int time = 5;
int score = 0;
int lock = 0;
int gameMode; // 2easy, 4medium, 8hard
int correct;

void labwork(void)
{
  while (gameActive == 0)
  {
    startScreen();
  }
  
  while (gameActive == 1 && time > -1)
  {
    char Str[31];
    if (IFS(0) & 0x100)                // time remaining
    {
      if (timeoutcount == 10)          // one second
      {
        sprintf(Str, "%s%d %s%d", "Score:", score, "Time:", time);
        display_string(3, Str);
        display_update();
        timeout = 0;
        time--;
        timeoutcount = 0;
        lock = 1;
      }
      timeoutcount++;
      IFSCLR(0) = 0x100;
    }

    if (userAnswering == 0)
    {
      correct = create_question(gameMode);
      userAnswering = 1;
    }

    if (((getbtns() == 1) || (getbtns() == 2) || (getbtns() == 4) || (getbtns() == 8)) && (timeout == 0)) 
    {
      userAnswering = 0;
      timeout = 1;
      if (correct == getbtns())
      {
        score++;
        time = time+3;
        sprintf(Str, "%s%d %s%d", "Score:", score, "Time:", time);
        display_string(3, Str);
        display_update();
      }
      else
      {
        time = time-1;
        sprintf(Str, "%s%d %s%d", "Score:", score, "Time:", time);
        display_string(3, Str);
        display_update();
      } 
    }
  }
  endScreen();
}

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
  display_string(0, "MATH GENIUS?");
  display_string(1, "BTN 2 EASY");
  display_string(2, "BTN 3 MEDIUM");
  display_string(3, "BTN 4 HARD");
  display_update();
    
  if((getbtns() != 0) && (getbtns() != 1))
  {
    display_clr();
    gameActive = 1;
    gameMode = getbtns(); // BTN2 - easy, BTN3 - medium, BTN4 - hard
  }
}

char finalScore[16];
char name[3] = {'A', 'A', 'A'};
char displayName[16];

int nameIndex = 0;
int nameEntry = 0;
int scoreboard_scores[3];
char scoreboard_names[3][3];
int sb_scoresIndex = 0;

void endScreen()
{
  display_clr();
  sprintf(finalScore,"Your score: %d", score);
  while(nameEntry == 0)
  {
    sprintf(displayName, "NAME: %c%c%c", name[0], name[1], name[2]);
    display_string(0, "   GAME OVER!");
    display_string(2, finalScore);
    display_string(3, displayName);
    display_update();
    display_string(0, "");
    display_update();

    if(IFS(0) & 0x100)
    {
      if(nameIndex < 3) 
      {
        if(getbtns() == 8)
        {
          if (name[nameIndex] == 90)  // If the char increments above Z it will reset to A
            name[nameIndex] = 65;
            
          name[nameIndex]++;
        }

        if(getbtns() == 4)
          nameIndex++;
      
      IFSCLR(0) = 0x100;
      }
      if(nameIndex == 3) 
      {
        nameEntry = 1;
        scoreboard_scores[3] = score;
      }
      
    }
  }
  // scoreBoard();
}

// void scoreBoard()
// {

// }

