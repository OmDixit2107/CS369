#include <stdio.h>
#include <string.h>
#include <ctype.h>

/**
 * @brief Encrypts text using the Affine cipher.
 *
 * @param plaintext The string to be encrypted.
 * @param ciphertext A buffer to store the encrypted string.
 * @param a The 'a' key value for the cipher.
 * @param b The 'b' key value for the cipher.
 */
void affineEncrypt(char plaintext[], char ciphertext[], int a, int b)
{
    int i;
    for (i = 0; i < strlen(plaintext); i++)
    {
        // Check if the character is an alphabet letter
        if (isalpha(plaintext[i]))
        {
            // Convert the character to its numeric value (A=0, B=1, ...)
            // We use toupper() to handle both upper and lower case letters
            int p_num = toupper(plaintext[i]) - 'A';

            // Apply the Affine cipher encryption formula: E(x) = (ax + b) mod 26
            int c_num = (a * p_num + b) % 26;

            // Convert the resulting number back to a character
            ciphertext[i] = c_num + 'A';
        }
        else
        {
            // If it's not a letter (like a space or punctuation), keep it as is
            ciphertext[i] = plaintext[i];
        }
    }
    // Null-terminate the ciphertext string
    ciphertext[strlen(plaintext)] = '\0';
}

int main()
{
    // Define the key (a, b) and the plaintext
    int a = 9;
    int b = 19;
    char plaintext[] = "INDIA";

    // Create a buffer for the ciphertext
    char ciphertext[strlen(plaintext) + 1];

    // Encrypt the plaintext
    affineEncrypt(plaintext, ciphertext, a, b);

    // Print the results
    printf("Affine Cipher Encryption\n");
    printf("--------------------------\n");
    printf("Key (a, b) : (%d, %d)\n", a, b);
    printf("Plaintext  : %s\n", plaintext);
    printf("Ciphertext : %s\n", ciphertext);
    printf("--------------------------\n");

    return 0;
}