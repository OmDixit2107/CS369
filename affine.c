#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Affine cipher encryption
void affineEncrypt(char plaintext[], char ciphertext[], int a, int b)
{
    int i;
    for (i = 0; i < strlen(plaintext); i++)
    {
        if (isalpha(plaintext[i]))
        {
            int p_num = toupper(plaintext[i]) - 'A';
            int c_num = (a * p_num + b) % 26;
            ciphertext[i] = c_num + 'A';
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
}

int main()
{
    int a = 5;
    int b = 21;
    char plaintext[] = "INDIA";

    char ciphertext[strlen(plaintext) + 1];

    affineEncrypt(plaintext, ciphertext, a, b);

    printf("Affine Cipher Encryption\n");
    printf("--------------------------\n");
    printf("Key (a, b) : (%d, %d)\n", a, b);
    printf("Plaintext  : %s\n", plaintext);
    printf("Ciphertext : %s\n", ciphertext);
    printf("--------------------------\n");

    return 0;
}