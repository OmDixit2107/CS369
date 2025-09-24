#include <stdio.h>

/**
 * @brief Implements the Extended Euclidean Algorithm to find integers x and y
 * such that ax + by = gcd(a, b).
 *
 * This function recursively calculates the GCD of 'a' and 'b' while also
 * determining the coefficients 'x' and 'y' from Bézout's identity.
 * The pointers x and y are used to return these coefficients back to the caller.
 *
 * @param a The first integer.
 * @param b The second integer.
 * @param x Pointer to an integer to store the coefficient of 'a'.
 * @param y Pointer to an integer to store the coefficient of 'b'.
 * @return The greatest common divisor of 'a' and 'b'.
 */
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
