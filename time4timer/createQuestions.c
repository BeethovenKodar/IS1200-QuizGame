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
int hScore;

// returns button for right answer
int create_question(int difficulty)     
{
    //
    if (difficulty == 2)      // EASY (numbers between 1-10)
    {
        UB = 11;
        LB = 1;
        hScore = 0;
    }
    if (difficulty == 4)      // MEDIUM (numbers between 10-20)
    {
        UB = 21;
        LB = 10;
        hScore = 1;
    }
    if (difficulty == 8)      // HARD (numbers between 80-100)
    {
        UB = 101;
        LB = 80;
        hScore = 2;
        
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
        case 3:	// 3 for modulus
        {
            result = num1%num2;
            sprintf(question,"What's %d '/. %d?\n", num1, num2);
            break;
        }
    }

    display_string(0, question);
    genAnswers(result);
    display_string(1, row1);
    display_string(2, row2);
    display_update();

    return resultBTN; 
}

int answers[4];

/* Generates the answers by intitally randomly inserting the right answer
   and then filling the remaining indexes with randomly generated wrong answers
 */
void genAnswers(int rightAnswer)
{
    int rightAnswerIndex = generateNum(0, 4);
    answers[rightAnswerIndex] = rightAnswer;

    int i = 0;
    for (i; i < 4; i++)
    {
        if (i != rightAnswerIndex)
        {
            int falseAnswer;
            int valid = 0;
            while (valid == 0)
            {
                falseAnswer = rightAnswer + generateNum(-5, 6);
                int j = 0;
                for (j; j < 4; j++)
                {
                    if (answers[j] == falseAnswer)
                    {
                        valid = 0;
                        break;
                    }
                    valid = 1;
                }
            }
            answers[i] = falseAnswer;
        }
    }
    resultBTN = invert(powerFunc(2, rightAnswerIndex));

    sprintf(row1, "A)%d  B)%d", answers[0], answers[1]);
    sprintf(row2, "C)%d  D)%d", answers[2], answers[3]);

    /*
    int rightAnswerIndex = generateNum(0, 4);
    answers[rightAnswerIndex] = rightAnswer;

    if (0 != rightAnswerIndex)
    {
        answers[0] = rightAnswer + generateNum(-6, -4);
    }
    if (1 != rightAnswerIndex)
    {1
        answers[1] = rightAnswer + generateNum(1, 3);
    }
    if (2 != rightAnswerIndex)
    {
        answers[2] = rightAnswer + generateNum(-3, -1);
    }
    if (3 != rightAnswerIndex)
    {
        answers[3] = rightAnswer + generateNum(3, 6);
    }

    resultBTN = invert(powerFunc(2, rightAnswerIndex));

    sprintf(row1, "A)%d  B)%d", answers[0], answers[1]);
    sprintf(row2, "C)%d  D)%d", answers[2], answers[3]);
    */
}

/* Since BTN4 is to the most left (answers are a, b, c, d) we have to invert the buttons*/
int invert(int num)
{
    switch (num)
    {
        case 8:
            return 1;
            break;
        case 4:
            return 2;
            break;
        case 2:
            return 4;
            break;
        case 1:
            return 8;
            break;    
    }
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

int hiScore(){
    return hScore;
}


// . /opt/mcb32tools/environment
