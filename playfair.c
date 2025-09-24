#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function prototypes
void generateKeyMatrix(char key[], char keyMatrix[5][5]);
void preparePlaintext(char plaintext[], char preparedText[]);
void encrypt(char preparedText[], char keyMatrix[5][5], char ciphertext[]);
void findPosition(char keyMatrix[5][5], char ch, int *row, int *col);

int main()
{
    char key[] = "MIDSEM";
    char plaintext[] = "VADODARA";
    char keyMatrix[5][5];

    // Buffers for processed text, size can be larger if needed
    char preparedText[100];
    char ciphertext[100];

    // 1. Generate the 5x5 key matrix
    generateKeyMatrix(key, keyMatrix);

    // 2. Prepare the plaintext (handle duplicates, odd length, J->I)
    preparePlaintext(plaintext, preparedText);

    // 3. Encrypt the prepared plaintext
    encrypt(preparedText, keyMatrix, ciphertext);

    // Print the results
    printf("Playfair Cipher Encryption\n");
    printf("--------------------------\n");
    printf("Key              : %s\n", key);
    printf("Plaintext        : %s\n", plaintext);
    printf("Prepared Plaintext: %s\n", preparedText);
    printf("Ciphertext       : %s\n", ciphertext);
    printf("--------------------------\n");

    return 0;
}

/**
 * @brief Generates the 5x5 key matrix.
 */
void generateKeyMatrix(char key[], char keyMatrix[5][5])
{
    int i, j, k = 0;
    // Use a flag array to keep track of letters already added to the matrix
    int alphabet_check[26] = {0};

    // Add unique characters from the key to the matrix
    for (i = 0; i < strlen(key); i++)
    {
        char ch = toupper(key[i]);
        if (ch == 'J')
            ch = 'I'; // Treat J as I

        if (alphabet_check[ch - 'A'] == 0)
        {
            keyMatrix[k / 5][k % 5] = ch;
            alphabet_check[ch - 'A'] = 1;
            k++;
        }
    }

    // Fill the rest of the matrix with the remaining letters of the alphabet
    for (i = 0; i < 26; i++)
    {
        if (i + 'A' == 'J')
            continue; // Skip J
        if (alphabet_check[i] == 0)
        {
            keyMatrix[k / 5][k % 5] = i + 'A';
            k++;
        }
    }
}

/**
 * @brief Prepares the plaintext for encryption.
 * - Converts to uppercase
 * - Replaces J with I
 * - Inserts 'X' between identical letters in a digraph
 * - Appends 'X' if the length is odd
 */
void preparePlaintext(char plaintext[], char preparedText[])
{
    int i, j = 0;
    for (i = 0; i < strlen(plaintext); i++)
    {
        char ch = toupper(plaintext[i]);
        if (isspace(ch))
            continue; // Ignore spaces
        if (ch == 'J')
            ch = 'I';

        // If the current char is same as the previous one, insert 'X'
        if (j > 0 && preparedText[j - 1] == ch)
        {
            preparedText[j++] = 'X';
        }
        preparedText[j++] = ch;
    }

    // If the final length is odd, append 'X'
    if (j % 2 != 0)
    {
        preparedText[j++] = 'X';
    }
    preparedText[j] = '\0'; // Null-terminate the string
}

/**
 * @brief Finds the row and column of a character in the key matrix.
 */
void findPosition(char keyMatrix[5][5], char ch, int *row, int *col)
{
    if (ch == 'J')
        ch = 'I';
    for (*row = 0; *row < 5; (*row)++)
    {
        for (*col = 0; *col < 5; (*col)++)
        {
            if (keyMatrix[*row][*col] == ch)
            {
                return;
            }
        }
    }
}

/**
 * @brief Encrypts the prepared plaintext using the key matrix.
 */
void encrypt(char preparedText[], char keyMatrix[5][5], char ciphertext[])
{
    int i;
    int r1, c1, r2, c2;
    for (i = 0; i < strlen(preparedText); i += 2)
    {
        // Find positions of the two characters in the digraph
        findPosition(keyMatrix, preparedText[i], &r1, &c1);
        findPosition(keyMatrix, preparedText[i + 1], &r2, &c2);

        // Case 1: Same row
        if (r1 == r2)
        {
            ciphertext[i] = keyMatrix[r1][(c1 + 1) % 5];
            ciphertext[i + 1] = keyMatrix[r2][(c2 + 1) % 5];
        }
        // Case 2: Same column
        else if (c1 == c2)
        {
            ciphertext[i] = keyMatrix[(r1 + 1) % 5][c1];
            ciphertext[i + 1] = keyMatrix[(r2 + 1) % 5][c2];
        }
        // Case 3: Rectangle
        else
        {
            ciphertext[i] = keyMatrix[r1][c2];
            ciphertext[i + 1] = keyMatrix[r2][c1];
        }
    }
    ciphertext[strlen(preparedText)] = '\0'; // Null-terminate
}