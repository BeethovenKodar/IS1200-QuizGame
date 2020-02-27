#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */
void *stdin, *stdout, *stderr; // Detta behövs för att använda standard biblioteken!

char question[31];    // the question to be displayed

char textQuestions[10][31] = {"Number of continents", 
                              "How many landscapes exist?", 
                              "How many countries are there?",
                              "How many genders exist?",
                              "When did WW1 start?",
                              "When did the Berlin wall fall?",
                              "When was KTH founded?",
                              "How old is Trump?",
                              "",
                              ""};

char textAnswers[10][31] = {"a)4 b)6 c)7 d)8",               //7 is correct     [2]
                            "a)10 b)25 c)18 d)20",           //20 is correct    [3]
                            "a)200 b)150 c)265 d)195",       //200 is correct   [0]
                            "a)2 b)3 c)infinite d)10",       //infinite         [2]
                            "a)1914 b)1913 c)1916 d)1942",   //1914             [0]
                            "a)2003 b)1989 c)1999 d)1990",   //1989             [1]
                            "a)1930 b)1827 c)1901 d)1854",   //1827             [1]
                            "a)53 b)68 c)65 d)73",           //73               [3]
                            "a) b) c) d)",                   //
                            "a) b) c) d)"};                  //
                        

int rightAnswers[10] ={2, 3, 0, 1, 0, 1, 1, 10, 10, 10};

int questionNumber;
int result;

void create_question()
{
    int qType = generateNum(0,2);
    if(qType == 1)
    {
        int num1 = generateNum(0,101);  // first term
        int num2 = generateNum(0,101);  // second term
        switch (generateNum(0,4))       // decides operation
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
        display_string(0, question);
        display_update();
    } 
    else
    {
        questionNumber = generateNum(0,4);
        display_string(0, textQuestions[questionNumber]);
        display_update();
    }
    
}

int generateNum(int min, int max)
{
    int random = (rand() % max-min) + min; // Yields a result between min and max-1
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