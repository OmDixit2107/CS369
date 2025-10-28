#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Caesar cipher encryption
void caesarEncrypt(char plaintext[], char ciphertext[], int key)
{
    int i;
    for (i = 0; i < strlen(plaintext); i++)
    {
        char ch = plaintext[i];

        if (isalpha(ch))
        {
            char base = islower(ch) ? 'a' : 'A';
            ciphertext[i] = (ch - base + key) % 26 + base;
        }
        else
        {
            ciphertext[i] = ch;
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
}

int main()
{
    char plaintext[] = "aeqwg";
    int key = 5;

    char ciphertext[strlen(plaintext) + 1];

    caesarEncrypt(plaintext, ciphertext, key);

    printf("Caesar Cipher Encryption\n");
    printf("------------------------\n");
    printf("Plaintext : %s\n", plaintext);
    printf("Key       : %d\n", key);
    printf("Ciphertext: %s\n", ciphertext);
    printf("------------------------\n");

    return 0;
}
