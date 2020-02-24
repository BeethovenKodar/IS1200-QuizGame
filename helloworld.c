#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int generateSum(int min, int max);
void testFunction(int iterations);

/*  Returns a random number
    between the range min and max (including max and min) */
int generateNum(int min, int max) {
    int random = (rand() % max-min + 1) + min;     // Yields a result between 
    printf("%d\n", random);         
    return random;                 
}

int main(void)
{
	printf("\n");
   	srand(time(NULL));							//init random generator
	int tORm = 1;								//0 for text, 1 for math
	int num1 = 0;
	int num2 = 0;
	int op = 0;
	int result = 0;
	char question[31];
	
	num1 = generateNum(0,100);
	num2 = generateNum(0,100);
	op = generateNum(0,3);
	
	if (tORm == 1)
	{
		switch (op)
		{
			case 0:									// 0 for addition
			{
				result = num1+num2;
				sprintf(question,"What's %d + %d?\n", num1, num2);
				break;
			}
		
			case 1:									// 1 for subtraction
			{
				result = num1-num2;
				sprintf(question,"What's %d - %d?\n", num1, num2);
				break;
			}
		
			case 2:									// 2 for multiplication
			{
				result = num1*num2;
				sprintf(question,"What's %d * %d?\n", num1, num2);
				break;
			}
			
			case 3:									// 3 for division
			{
				result = num1/num2;
				sprintf(question,"What's %d / %d?\n", num1, num2);
				break;
			}
		}	
		printf("%s\n", question);
	}

	else
		{
			/*array of questions*/
			/*array of answers*/
		}

	return 0;
}

void testFunction(int iterations) {
    for(int i = 0; i < iterations; i++) {
        generateNum(10, 20);
    }
}

// void conc(char* p, char* q) {
//    int c, d;
   
//    c = 0;
 
//    while (p[c] != '\0') {
//       c++;
//    }
 
//    d = 0;
 
//    while (q[d] != '\0') {
//       p[c] = q[d];
//       d++;
//       c++;    
//    }
 
//    p[c] = '\0';
// }

// gcc -o hello helloworld.c && ./hello
