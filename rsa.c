#include <stdio.h>

// 1. Function to calculate GCD (to check if e is legitimate)
long long gcd(long long a, long long b)
{
    while (b != 0)
    {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// 2. Extended Euclidean Algorithm to find Modular Inverse (to find d)
long long modInverse(long long e, long long phi)
{
    long long m0 = phi;
    long long y = 0, x = 1;

    if (phi == 1)
        return 0;

    while (e > 1)
    {
        // q is quotient
        long long q = e / phi;
        long long t = phi;

        // phi is remainder now, process same as Euclid's algo
        phi = e % phi, e = t;
        t = y;

        // Update y and x
        y = x - q * y;
        x = t;
    }

    // Make x positive
    if (x < 0)
        x += m0;

    return x;
}

// 3. Modular Exponentiation (to find ciphertext c)
// Computes (base^exp) % mod
long long power(long long base, long long exp, long long mod)
{
    long long res = 1;
    base = base % mod;

    while (exp > 0)
    {
        // If exp is odd, multiply base with result
        if (exp % 2 == 1)
            res = (res * base) % mod;

        // exp must be even now
        exp = exp / 2;
        base = (base * base) % mod;
    }
    return res;
}

int main()
{
    long long p = 761;
    long long q = 769;
    long long e = 941;
    long long m = 600;

    long long n = p * q;
    long long phi = (p - 1) * (q - 1);

    printf("--- RSA Calculation Results ---\n");
    printf("p: %lld, q: %lld, n: %lld\n", p, q, n);
    printf("Phi(n): %lld\n", phi);
    printf("e: %lld\n", e);
    printf("Message (m): %lld\n", m);
    printf("-------------------------------\n");

    if (gcd(e, phi) != 1)
    {
        printf("ERROR: e is NOT legitimate. GCD(e, phi) != 1.\n");
        return 0;
    }
    else
    {
        printf("Check: e is legitimate (Coprime to Phi).\n");
    }

    long long d = modInverse(e, phi);
    printf("Private Key (d): %lld\n", d);

    long long c = power(m, e, n);
    printf("Ciphertext (c): %lld\n", c);

    return 0;
}