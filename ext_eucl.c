#include <stdio.h>

int extendedEuclidean(int a, int b, int *x, int *y)
{
    // Base case for the recursion
    if (a == 0)
    {
        *x = 0;
        *y = 1;
        return b;
    }

    int x1, y1; // To store results of the recursive call

    // Recursive call, following the algorithm's steps
    int gcd = extendedEuclidean(b % a, a, &x1, &y1);

    // Update x and y using results of the recursive call.
    // This is the "backward" substitution step, done elegantly through recursion.
    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcd;
}

int main()
{
    int a = 23;
    int b = 43;
    int x, y;

    int g = extendedEuclidean(a, b, &x, &y);

    printf("Given the equation: %dx + %dy = gcd(%d, %d)\n", a, b, a, b);
    printf("The greatest common divisor (gcd) is: %d\n", g);
    printf("The values are:\n");
    printf("x = %d\n", x);
    printf("y = %d\n", y);
    printf("\nVerification: (%d * %d) + (%d * %d) = %d\n", a, x, b, y, a * x + b * y);

    return 0;
}
