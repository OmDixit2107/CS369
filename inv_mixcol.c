#include <stdio.h>

// --- YOUR EXISTING FUNCTIONS ---

// Multiply by 2 (x)
unsigned char xf(unsigned char A)
{
    unsigned char temp;
    temp = A << 1;
    if ((A >> 7) == 1)
    {
        temp = temp ^ 27; // XOR with 0x1B (polynomial)
    }
    return temp;
}

// --- NEW FUNCTIONS ADDED FOR INVERSE MIX COLUMN ---

// Helper: Multiply by 4 (x^2)
unsigned char xf4(unsigned char n)
{
    return xf(xf(n));
}

// Helper: Multiply by 8 (x^3)
unsigned char xf8(unsigned char n)
{
    return xf(xf(xf(n)));
}

// AES Inverse Multiplications using Distributive Property:
// 9  = 8 + 1
// 11 = 8 + 2 + 1
// 13 = 8 + 4 + 1
// 14 = 8 + 4 + 2

unsigned char mul9(unsigned char n)
{
    return xf8(n) ^ n;
}

unsigned char mul11(unsigned char n)
{
    return xf8(n) ^ xf(n) ^ n;
}

unsigned char mul13(unsigned char n)
{
    return xf8(n) ^ xf4(n) ^ n;
}

unsigned char mul14(unsigned char n)
{
    return xf8(n) ^ xf4(n) ^ xf(n);
}

// Function to perform Inverse MixColumn on a single column array
void invMixColumnSingle(unsigned char c[4])
{
    unsigned char s0 = c[0];
    unsigned char s1 = c[1];
    unsigned char s2 = c[2];
    unsigned char s3 = c[3];

    // The Inverse MixColumn Matrix:
    // 14 11 13 09
    // 09 14 11 13
    // 13 09 14 11
    // 11 13 09 14

    c[0] = mul14(s0) ^ mul11(s1) ^ mul13(s2) ^ mul9(s3);
    c[1] = mul9(s0) ^ mul14(s1) ^ mul11(s2) ^ mul13(s3);
    c[2] = mul13(s0) ^ mul9(s1) ^ mul14(s2) ^ mul11(s3);
    c[3] = mul11(s0) ^ mul13(s1) ^ mul9(s2) ^ mul14(s3);
}

int main()
{
    // Input from your problem statement
    unsigned char col[4] = {123, 212, 88, 77};

    printf("Input Column: \n");
    for (int i = 0; i < 4; i++)
        printf("%d ", col[i]);
    printf("\n\n");

    // Perform Inverse MixColumn
    invMixColumnSingle(col);

    printf("Output after Inverse MixColumn: \n");
    for (int i = 0; i < 4; i++)
    {
        printf("%d ", col[i]);
    }
    printf("\n");

    return 0;
}