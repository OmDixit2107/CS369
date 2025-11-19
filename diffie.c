#include <stdio.h>

// Modular Exponentiation Function
// Calculates (base^exp) % mod efficiently
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
    // --- INPUT VARIABLES ---
    long long p = 181;           // Prime Modulus
    long long g = 2;             // Generator
    long long alice_secret = 97; // Alice's Private Key (a)
    long long bob_secret = 82;   // Bob's Private Key (b)
    // -----------------------

    long long alice_public = power(g, alice_secret, p);
    long long bob_public = power(g, bob_secret, p);

    printf("Alice's Public Key (A = g^a mod p): %lld\n", alice_public);
    printf("Bob's Public Key   (B = g^b mod p): %lld\n", bob_public);

    long long shared_secret_alice = power(bob_public, alice_secret, p);

    long long shared_secret_bob = power(alice_public, bob_secret, p);

    printf("Shared Secret (Calculated by Alice): %lld\n", shared_secret_alice);
    printf("Shared Secret (Calculated by Bob):   %lld\n", shared_secret_bob);

    if (shared_secret_alice == shared_secret_bob)
    {
        printf("\nSUCCESS: Key Exchange Verified.\n");
    }
    else
    {
        printf("\nERROR: Mismatch in shared keys.\n");
    }

    return 0;
}