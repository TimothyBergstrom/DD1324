#include <stdio.h>
#include <stdlib.h>


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

    printf("%d %ld\n", n, fib(n));
}
