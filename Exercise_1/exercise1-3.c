#include <stdio.h>
#include <stdlib.h>
#include <time.h>


long fib (long n)  // 64 bits
{
    if ((n == 1) || (n == 2))
    {
        return 1;
    }
    else
    {
        return fib(n - 1) + fib(n -2);
    }
}

long fib_fast (long n) {
    if ((n == 1) || (n == 2)) {
        return 1;
    }
    long long n1 = 1;  // long long because I need to handle large numbers
    long long n2 = 1;
    long long n3 = 0;
    for(long i = 2; i < n; i++) { // Important: i needs to be same type as n
        n3 = n2 + n1;
        n1 = n2;
        n2 = n3;
    }
    return n3;
}

int main(int argc, char** argv)
{
    int n;

    if (argc < 2) {
      fprintf(stderr, "Recommend computing fib 45 to start\n");
      fprintf(stderr, "time requirement roughly doubles for each succeeding fib number\n");
      fprintf(stderr, "Usage: fib n\n");
      return -1;
    }
    n = atoi(argv[1]);
    
    /* I want to be fair when comparing the time it takes to run a function in
    python and c, so instead of using "time" in the linux terminal, I will measure
    the time it takes to run the function. Of course, you have to take into consideration
    that python takes more time to initialize than a compiled c program */
    clock_t start = clock();  // Start clock
    printf("%d %ld\n", n, fib(n));  // Run function
    clock_t stop = clock();  // Stop clock
    /* Each machine has a certain clock rate. clock() gets the clocks between each 
    point, but I want it to seconds, which is why I use CLOCKS_PER_SEC */
    double time_spent = (double)(stop - start) / CLOCKS_PER_SEC;
    printf("%.6f seconds to run function\n", time_spent);
    
    // No need to declare variables here, just overwrite them
    // Is this a bad practice? Should I delocate memory and declare them again?
    start = clock(); 
    printf("%d %ld\n", n, fib_fast(n)); 
    stop = clock();
    time_spent = (double)(stop - start) / CLOCKS_PER_SEC;
    printf("%.6f seconds to run the fast function\n", time_spent);
    
    /* The regular function is several times of magnitude faster than the python code:
    Python: XX seconds
    C: XX seconds
    
    However, the "fast" function that I created was much faster on both
    Python: XX seconds
    C: XX seconds
    */
}