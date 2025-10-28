#include <stdio.h>

long long power(long long base, long long exp, long long mod)
{
    long long res = 1;

    // Reduce base modulo mod to keep numbers small
    base %= mod;

    while (exp > 0)
    {
        // If the exponent is odd, multiply the base with the result
        if (exp % 2 == 1)
        {
            // Use 64-bit multiplication and then take the modulus
            // to prevent overflow
            res = (res * base) % mod;
        }

        // The exponent must be even now, so we can halve it
        exp >>= 1; // equivalent to exp = exp / 2

        // Square the base and take the modulus
        base = (base * base) % mod;
    }
    return res;
}

void findModularInverse(long long a, long long p)
{
    // Calculate a^(p-2) mod p
    long long inverse = power(a, p - 2, p);
    printf("Let p = %lld\n", p);
    printf("Let a = %lld\n\n", a);
    printf("The multiplicative inverse of %lld under mod %lld is: %lld\n", a, p, inverse);
}

int main()
{
    // p = 2147483647 is the 8th Mersenne prime (2^31 - 1), a large prime number.
    long long p = 2147483647;
    long long a = 13;

    findModularInverse(a, p);

    return 0;
}
