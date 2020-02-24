/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */
#include <stdlib.h>
void *stdin, *stdout, *stderr; // Detta behövs för att använda standard biblioteken!

char question[31];    // the question to be displayed

char textQuestions[3][31]= {"Capital of Sweden?", "Capital of Finland?", "Capital of Norway?"};

// char textAnswers[];

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  TMR2 = 0;                                  
  PR2 = (80000000 / 256 ) / 10;      //count in prescale (still 1s period) and also divide by 10 for 100ms
  T2CONSET = 0x8070;                 //start timer and set prescaling to 256 1000 0000 0111 0000 --> 8070
}

/* This function is called repetitively from the main program */
void labwork( void )
{ 
  
  // display_question(create_question());
  create_question();
  display_string(0, question);
  display_update();
}

// void display_question(char q[]) 
// {
//    int count = 0;
//    int line = 0;
//    while (q != '\0') {
//      count++;
//      if(count == 15) {
//      }
//    }
//   display_string();
// }

// void display_answers()
// {
  
// }

int timeoutcount = 0;

void create_question()
{
  if (IFS(0) & 0x100)
  {                                                                   //  
    IFS(0) = IFS(0) & 0xFEFF;
    timeoutcount++;
  {

  if(timeoutcount == 10) 
  {
    timeoutcount = 0; 
    srand(7532790753);
    // int textOrMath = generateNum(0,1);
    int textOrMath = 1;
    if(textOrMath == 1)                                               // Math question
    {
      int result = 0;
      int num1 = generateNum(0,100);
      int num2 = generateNum(0,100);
      
      switch (generateNum(0,3))                                       // decides operation
      {
        case 0:									                                      // 0 for addition
        {
          result = num1+num2;
          sprintf(question,"What's %d + %d?\n", num1, num2);
          break;
        }
      
        case 1:								                                      	// 1 for subtraction
        {
          result = num1-num2;
          sprintf(question,"What's %d - %d?\n", num1, num2);
          break;
        }
      
        case 2:								                                       	// 2 for multiplication
        {
          result = num1*num2;
          sprintf(question,"What's %d * %d?\n", num1, num2);
          break;
        }
        
        case 3:								                                      	// 3 for division
        {
          num1 = generateNum(0,100);
          num2 = generateNum(0,100);
          result = num1/num2;
          sprintf(question,"What's %d / %d?\n", num1, num2);
          break;
        }
        
    }
  }
  else
  {
  display_string(0, "textQuestion");
  }
    }

}

int generateNum(int min, int max)
{
    int random = (rand() % max-min) + min;     // Yields a result between min and max input
    return random;                  
} 