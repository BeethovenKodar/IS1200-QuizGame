#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */
void *stdin, *stdout, *stderr; // Detta behövs för att använda standard biblioteken!

char question[31];    // the question to be displayed

char textQuestions[10][31] = {"Number of continents", "How many landscapes exist?", "How many countries are there?"};

char textAnswers[10][31] = {"a)4 b)6 c)7 d)8", "a)10 b)25 c)18 d)20", "a)200 b)150 c)265 d)195"};

int rightAnswer[10] ={2, 4, 1 };


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
    int random = (rand() % max-min) + min;     // Yields a result between min and max-1
    return random;                  
} 

// void display_question(char str) {
//     int chars = 0;
//     int wordLength = 0;
//     int row = 0;
//     char rowStr[31];
//     int pos = 0;
//     while (str != '\0') 
//     {
//         while (str != 0x20 && (wordLength <= 16-chars))
//         {
//             wordLength++;
//             chars++;
//             pos++;
//             str++;
//         }
//         display_string(row, rowStr)
//         display_update();
//         row++;
       
//     }
// }