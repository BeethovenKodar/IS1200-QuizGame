#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int generateSum(int min, int max);
void testFunction(int iterations);

int main(void) {
    srand(time(NULL));
    testFunction(5);
    return 0;
}

/*  Returns a random number
    between the range min and max (including max and min) */
int generateNum(int min, int max) {
    int random = (rand() % max) + min;     // Yields a result between 
    printf("%d\n", random);         
    return random;                  
}

void testFunction(int iterations) {
    for(int i = 0; i < iterations; i++) {
        generateNum(1, 5);
    }
}
// gcc -o hello helloworld.c && ./hello