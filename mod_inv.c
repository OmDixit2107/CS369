#include <stdio.h>

/**
 * @brief Calculates (base^exp) % mod using the method of exponentiation by squaring.
 * * This function is efficient for large exponents, as it reduces the number of
 * multiplications required. It's essential for cryptographic calculations and
 * problems involving large numbers, preventing overflow by taking the modulus
 * at each step.
 * * @param base The base of the exponentiation.
 * @param exp The exponent.
 * @param mod The modulus.
 * @return The result of (base^exp) % mod.
 */
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

/**
 * @brief Finds the multiplicative inverse of 'a' under a prime modulus 'p'.
 * * This function uses Fermat's Little Theorem, which states that if p is a prime number,
 * then for any integer a not divisible by p, we have a^(p-1) ≡ 1 (mod p).
 * This can be rewritten as a * a^(p-2) ≡ 1 (mod p).
 * Therefore, the multiplicative inverse of 'a' is a^(p-2) mod p.
 * * @param a The number to find the inverse of.
 * @param p The prime modulus.
 */
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
