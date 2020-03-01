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
  
  srand(TMR3);                 // give random generator seeds from TMR3
}

int gameActive = 0;
int time = 15;
int score = 0;
int gameMode;  // 2easy, 4medium, 8hard
int correct;

void labwork(void)
{
  //
  int userAnswering = 0;
  int timeoutcount = 10;
  // int timeout = 1;
  //
  while (gameActive == 0)
  { 
    startScreen();
  }
  
  while (gameActive == 1 && time > -1 && getsw() != 0x4) //GETSW BARA FÖR DEBUG
  {
    char Str[31];
    if (IFS(0) & 0x100)                // time remaining
    {
      if (timeoutcount == 10)          // one second
      {
        sprintf(Str, "%s%d %s%d", "Score:", score, "Time:", time);
        display_string(3, Str);
        display_update();
        // timeout--;
        time--;
        timeoutcount = 0;
      }
      timeoutcount++;
      IFSCLR(0) = 0x100;
    }

    if (userAnswering == 0)
    {
      sprintf(Str, "%s%d %s%d", "Score:", score, "Time:", time);
      display_string(3, Str);
      display_update();
      correct = create_question(gameMode);
      userAnswering = 1;
      delay(2500);
    }

    if (((getbtns() == 1) || (getbtns() == 2) || (getbtns() == 4) || (getbtns() == 8))) 
    {
      userAnswering = 0;
      //timeout = 1;
      TMR3 = TMR3 + (getbtns() * 1013);
      if (correct == getbtns())
      {
        score++;
        time = time+3;
      }
      else
      {
        time = time-2;
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

int scoreboard_scores[3] = {0,0,0};
char scoreboard_names[3][4] = {"AAA","AAA","AAA"}; // kan ta bort andra indexet?

void endScreen()
{
  int nameIndex = 0;
  char finalScore[16];
  char displayName[16];
  char name[4] = {'A', 'A', 'A', '\0'};
  display_clr();
  sprintf(finalScore,"Your score: %d", score);
  while (nameIndex < 3)
  {
    sprintf(displayName, "NAME: %c%c%c", name[0], name[1], name[2]);
    display_string(0, "   GAME OVER!");
    display_string(2, finalScore);
    display_string(3, displayName);
    display_update();

    if (getbtns() == 8)
    {
      if (name[nameIndex] == 90)  // If the char increments above Z it will reset to A
        name[nameIndex] = 65;

      name[nameIndex]++;

    }

    if (getbtns() == 4)
      nameIndex++;
    
    delay(1250);
  }
  
  if (score >= scoreboard_scores[2]) 
  {
    scoreboard_scores[2] = score;
    strcpy(scoreboard_names[2], name);
    sort();
  }
  
  scoreBoard();
  time = 5;
  score = 0;
  gameActive = 0;
}

void scoreBoard()
{
  char Str[31];
  display_clr();
  display_string(0, "   Scoreboard");
  int i = 0;
  for(i; i < 3; i++)
  {
    sprintf(Str, " %s %s%d", scoreboard_names[i], "Score:", scoreboard_scores[i]);
    display_string(i+1, Str);
  }
  display_update();
  delay(25000);
}

void swap(int *a, int *b) 
{ 
    int temp = *a; 
    *a = *b; 
    *b = temp; 
} 

void swapStrings(char **a, char **b) 
{
    char *t;
    t = *a;
    *a = *b;
    *b = t;
}

void sort()
{
  int i = 0;
  int biggestIndex = 0;
  for (i; i < 3; i++)
  {
    biggestIndex = i;
    int j = 0;
    for (j = i+1; j < 3; j++)
    {
      if (scoreboard_scores[biggestIndex] < scoreboard_scores[j])
        biggestIndex = j;
    }
    swap(&scoreboard_scores[biggestIndex], &scoreboard_scores[i]);
    swapStrings(&scoreboard_names[biggestIndex], &scoreboard_names[i]);
  }
  
}

//. /opt/mcb32tools/environment
