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
  
  srand(TMR3);                        // give random generator seeds from TMR3
}

int gameActive = 0;
int time = 6;
int score = 0;
int gameMode;  // 2easy, 4medium, 8hard
int correct;

void labwork(void)
{
  int userAnswering = 0;
  int timeoutcount = 10;

  /* Loop while difficulty isn't decided */
  while (gameActive == 0)
  { 
    startScreen();
  }
  
  /* Spelets loop. Här spelar användaren. GameActive bestämmer om startskärmen eller spelskärmen visas
     Spelet avslutas när time är mindre än 0 */
  while (gameActive == 1 && time > -1 && getsw() != 0x4) //  GETSW BARA FÖR DEBUG
  {
    char Str[31];
    if (IFS(0) & 0x100)                
    {
      if (timeoutcount == 10)          // gives one second
      {
        sprintf(Str, "%s%d %s%d", "Score:", score, "Time:", time); // time remaining is updated once a second
        display_string(3, Str);
        display_update();
        time--;
        timeoutcount = 0;
      }
      timeoutcount++;
      IFSCLR(0) = 0x100;
    }

    /* Creates a new question if the user isn't answering */
    if (userAnswering == 0)
    {
      sprintf(Str, "%s%d %s%d", "Score:", score, "Time:", time);
      display_string(3, Str);
      display_update();
      correct = create_question(gameMode);
      userAnswering = 1;
      delay(2500);
    }

    /* Handles the answer buttons, correct or incorrect answer */
    if (((getbtns() == 1) || (getbtns() == 2) || (getbtns() == 4) || (getbtns() == 8))) 
    {
      userAnswering = 0;
      TMR3 = TMR3 + (getbtns() * 1013);   // Not working properly
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

/* method to clear the display when moving from eg. startscreen to questions */
void display_clr()
{
  display_string(0, "");
  display_string(1, "");
  display_string(2, "");
  display_string(3, "");
  display_update();
}

/* Startscreen where the user gets to choose difficulty */
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

/* Three arrays in an array for the three difficulties */
int scoreboard_scores[3][3] = {{0,0,0}, {0,0,0}, {0,0,0}};
char scoreboard_names[3][3][4] = {{"AAA","AAA","AAA"}, {"AAA","AAA","AAA"}, {"AAA","AAA","AAA"}};

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

    if (getbtns() == 8)           // Moves to next char in ASCII table
    {
      if (name[nameIndex] == 90)  // If the char increments above Z it will reset to A
        name[nameIndex] = 65;

      name[nameIndex]++;

    }

    if (getbtns() == 4)           // Move to next char to edit
      nameIndex++;
    
    delay(1250);
  }
  
  /* Check to see if the produced score should be put on the scoreboard */
  if (score >= scoreboard_scores[hiScore()][2]) 
  {
    scoreboard_scores[hiScore()][2] = score;
    strcpy(scoreboard_names[hiScore()][2], name);
    sort();
  }
  
  /* Reset variables */
  scoreBoard();
  time = 6;
  score = 0;
  gameActive = 0;
}

/* Checks which scoreboard to display, based of difficulty */
void scoreBoard()
{
  char Str[31];
  display_clr();
  if (hiScore() == 0)
  {
    display_string(0, "Scoreboard E:");
  }
  if (hiScore() == 1)
  {
    display_string(0, "Scoreboard M:");
  }  
  if (hiScore() == 2)
  {
    display_string(0, "Scoreboard H:");
  }
  display_update();
  
  int i = 0;
  for(i; i < 3; i++)
  {
    sprintf(Str, "%s %s%d", scoreboard_names[hiScore()][i], "Score:", scoreboard_scores[hiScore()][i]);
    display_string(i+1, Str);
  }
  display_update();
  delay(60000);
}

/* Normal swap of two numbers with temp variable */
void swap(int *a, int *b) 
{ 
    int temp = *a; 
    *a = *b; 
    *b = temp; 
} 

/* Swap strings. char ** because "pointer to pointer to char" */
void swapStrings(char **a, char **b) 
{
    char *t;
    t = *a;
    *a = *b;
    *b = t;
}

/* Sort the active scoreboard with selection sort  */
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
      if (scoreboard_scores[hiScore()][biggestIndex] < scoreboard_scores[hiScore()][j])
        biggestIndex = j;
    }
    swap(&scoreboard_scores[hiScore()][biggestIndex], &scoreboard_scores[hiScore()][i]);
    swapStrings(&scoreboard_names[hiScore()][biggestIndex], &scoreboard_names[hiScore()][i]);
  }
  
}

//. /opt/mcb32tools/environment
