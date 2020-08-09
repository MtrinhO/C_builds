#include <stdio.h>

//Collatz conjecture algorithm
int collatz(int n)
    {
            //Base case
        if (n==1)
        {
            return 0;
        }
        //Recursive odd case
        else if (n%2!=0)
        {
            return 1 + collatz(3*n+1);
        }
        //Recursive even case
        else
        {
            return 1 + collatz(n/2);
        }
    }

//Input number, return number of steps
int main(void)
{
    int n = get_int("Collatz conjecture input: \n");
    collatz(n);
    printf("If you input %i, you will need %i steps via collatz conjecture to reach 1. \n", n, collatz(n));
}