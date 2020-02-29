#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

void *stdin, *stdout, *stderr; // Detta behövs för att använda standardbiblioteken!                        

int result;         // result of the task
int resultBTN;      // button that gives correct answer
int UB;             // upper bound for random
int LB;             // lower bound for random
char question[16];  // generated question
char row1[16];      // row 1 on display
char row2[16];      // row 2 on display

// returns button for right answer
int create_question(int difficulty)     
{
    //
    if (difficulty == 2)      // EASY (numbers between 1-10)
    {
        UB = 11;
        LB = 1;
    }
    if (difficulty == 4)      // MEDIUM (numbers between 10-20)
    {
        UB = 21;
        LB = 10;
    }
    if (difficulty == 8)      // HARD (numbers between 80-100)
    {
        UB = 101;
        LB = 80;
    }
    //

    //
    int num1 = generateNum(LB, UB);      // first term
    int num2 = generateNum(LB, UB);      // second term
    switch (generateNum(0,4))            // decides operation
    {
        case 0: // 0 for addition
        {
            result = num1+num2;
            sprintf(question,"What's %d + %d?\n", num1, num2);
            break;
        }
        case 1:	// 1 for subtraction
        {
            result = num1-num2;
            sprintf(question,"What's %d - %d?\n", num1, num2);
            break;
        }
        case 2:	// 2 for multiplication
        {
            result = num1*num2;
            sprintf(question,"What's %d * %d?\n", num1, num2);
            break;
        }
        case 3:	// 3 for division
        {
            result = num1/num2;
            sprintf(question,"What's %d / %d?\n", num1, num2);
            break;
        }
    }
    //

    display_string(0, question);
    genAnswers(result);
    display_string(1, row1);
    display_string(2, row2);
    display_update();

    return resultBTN; 
}

int answers[4];

void genAnswers(int rightAnswer)
{
    int rightAnswerIndex = generateNum(0,4);
    answers[rightAnswerIndex] = rightAnswer;

    int i = 0;
    int j = 0;
    int valid = 0;
    int generatedFalseNumber;
    while(i < 4)
    {
        if (i != rightAnswerIndex)
        {
            generatedFalseNumber = rightAnswer + generateNum(-5,6);
            while (valid != 1)
            {
                for (j; j < i; j++)
                {
                    if (answers[j] == generatedFalseNumber)
                        generatedFalseNumber = rightAnswer + generateNum(-5,6);
                    if (j == 3)
                        break;
                }
            }
            answers[i] = generatedFalseNumber;
        }
        i++;
    }
    resultBTN = powerFunc(2, rightAnswerIndex); 

    sprintf(row1, "A)%d  B)%d", answers[0], answers[1]);
    sprintf(row2, "C)%d  D)%d", answers[2], answers[3]);
}

int generateNum (int min, int max)          // Gives a result [min, max-1]
{
    int random = (rand() % (max-min)) + min; 
    return random;                  
} 

int powerFunc (int base, int exponent)
{
    int i;
    int number = 1;

    for (i = 0; i < exponent; ++i)
        number *= base;

    return(number);
}

