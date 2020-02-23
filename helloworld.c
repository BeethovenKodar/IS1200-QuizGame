#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int generateSum(int min, int max);
void testFunction(int iterations);

int main(void) {
    srand(time(NULL));
    testFunction(2);
    return 0;
}

/*  Returns a random number
    between the range min and max (including max and min) */
int generateNum(int min, int max) {
    int random = (rand() % max-min) + min;     // Yields a result between 
    printf("%d\n", random);         
    return random;                  
}

void testFunction(int iterations) {
    for(int i = 0; i < iterations; i++) {
        generateNum(10, 20);
    }
}

void conc(char* p, char* q) {
   int c, d;
   
   c = 0;
 
   while (p[c] != '\0') {
      c++;
   }
 
   d = 0;
 
   while (q[d] != '\0') {
      p[c] = q[d];
      d++;
      c++;    
   }
 
   p[c] = '\0';
}

// gcc -o hello helloworld.c && ./hello