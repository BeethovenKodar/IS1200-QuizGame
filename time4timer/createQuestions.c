#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */
void *stdin, *stdout, *stderr; // Detta behövs för att använda standard biblioteken!

char question[31];    // the question to be displayed

char* textQuestions[3] = {"Number of continents?", "Capital of Finland?", "Capital of Norway?"};

char textAnswers[3][4] = {};


void create_question()
{
    int qType = generateNum(0,2);
    if(qType == 1)
    {
        int result = 0;
        int num1 = generateNum(0,101);
        int num2 = generateNum(0,101);
        switch (generateNum(0,4))                                           // decides operation
        {
            case 0:									                        // 0 for addition
            {
                result = num1+num2;
                sprintf(question,"What's %d + %d?\n", num1, num2);
                break;
            }

            case 1:								                            // 1 for subtraction
            {
                result = num1-num2;
                sprintf(question,"What's %d - %d?\n", num1, num2);
                break;
            }

            case 2:								                           	// 2 for multiplication
            {
                result = num1*num2;
                sprintf(question,"What's %d * %d?\n", num1, num2);
                break;
            }

            case 3:								                          	// 3 for division
            {
                result = num1/num2;
                sprintf(question,"What's %d / %d?\n", num1, num2);
                break;
            }
        }
        // För matte frågor
        display_string(0, question);
        display_update();
    } 
    else
    {
        display_string(0, textQuestions[generateNum(0,4)]);
        display_update();
    }
    
}

int generateNum(int min, int max)
{
    int random = (rand() % max-min) + min;     // Yields a result between min and max input
    return random;                  
} 