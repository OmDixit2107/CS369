#include <stdio.h>
#include <string.h>
#include <ctype.h>

/**
 * @brief Encrypts text using the Caesar (Shift) cipher.
 * * @param plaintext The string to be encrypted.
 * @param ciphertext A buffer to store the encrypted string.
 * @param key The integer value to shift the letters by.
 */
void caesarEncrypt(char plaintext[], char ciphertext[], int key)
{
    int i;
    for (i = 0; i < strlen(plaintext); i++)
    {
        char ch = plaintext[i];

        // Encrypt only alphabetic characters
        if (isalpha(ch))
        {
            // Determine the base character ('a' for lowercase, 'A' for uppercase)
            char base = islower(ch) ? 'a' : 'A';

            // Apply the shift formula: C = (P + K) % 26
            // 1. Convert char to number (0-25): (ch - base)
            // 2. Add the key: (ch - base + key)
            // 3. Wrap around the alphabet: (... % 26)
            // 4. Convert back to char: (... + base)
            ciphertext[i] = (ch - base + key) % 26 + base;
        }
        else
        {
            // If not a letter, keep the character as is
            ciphertext[i] = ch;
        }
    }
    // Add the null terminator to mark the end of the string
    ciphertext[strlen(plaintext)] = '\0';
}

int main()
{
    // Define the plaintext and the key
    char plaintext[] = "aeqwg";
    int key = 5;

    // Create a buffer for the ciphertext (+1 for the null terminator)
    char ciphertext[strlen(plaintext) + 1];

    // Call the encryption function
    caesarEncrypt(plaintext, ciphertext, key);

    // Print the results
    printf("Caesar Cipher Encryption\n");
    printf("------------------------\n");
    printf("Plaintext : %s\n", plaintext);
    printf("Key       : %d\n", key);
    printf("Ciphertext: %s\n", ciphertext);
    printf("------------------------\n");

    return 0;
}