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
    char key[] = "aedoqmw";
    char plaintext[] = "iamd";
    char keyMatrix[5][5];

    char preparedText[100];
    char ciphertext[100];

    generateKeyMatrix(key, keyMatrix);
    preparePlaintext(plaintext, preparedText);
    encrypt(preparedText, keyMatrix, ciphertext);

    printf("Playfair Cipher Encryption\n");
    printf("--------------------------\n");
    printf("Key              : %s\n", key);
    printf("Plaintext        : %s\n", plaintext);
    printf("Prepared Plaintext: %s\n", preparedText);
    printf("Ciphertext       : %s\n", ciphertext);
    printf("--------------------------\n");

    return 0;

    // Generates the 5x5 key matrix
    void generateKeyMatrix(char key[], char keyMatrix[5][5])
    {
        int i, j, k = 0;
        int alphabet_check[26] = {0};

        for (i = 0; i < strlen(key); i++)
        {
            char ch = toupper(key[i]);
            if (ch == 'J')
                ch = 'I';

            if (alphabet_check[ch - 'A'] == 0)
            {
                keyMatrix[k / 5][k % 5] = ch;
                alphabet_check[ch - 'A'] = 1;
                k++;
            }
        }

        for (i = 0; i < 26; i++)
        {
            if (i + 'A' == 'J')
                continue;
            if (alphabet_check[i] == 0)
            {
                keyMatrix[k / 5][k % 5] = i + 'A';
                k++;
            }
        }

        // Prepares plaintext by handling duplicates, odd length, and J->I conversions
        void preparePlaintext(char plaintext[], char preparedText[])
        {
            int i, j = 0;
            for (i = 0; i < strlen(plaintext); i++)
            {
                char ch = toupper(plaintext[i]);
                if (isspace(ch))
                    continue;
                if (ch == 'J')
                    ch = 'I';

                if (j > 0 && preparedText[j - 1] == ch)
                {
                    preparedText[j++] = 'X';
                }
                preparedText[j++] = ch;
            }

            if (j % 2 != 0)
            {
                preparedText[j++] = 'X';
            }
            preparedText[j] = '\0';

            // Finds the position of a character in the key matrix
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
                    findPosition(keyMatrix, preparedText[i], &r1, &c1);
                    findPosition(keyMatrix, preparedText[i + 1], &r2, &c2);

                    if (r1 == r2)
                    {
                        ciphertext[i] = keyMatrix[r1][(c1 + 1) % 5];
                        ciphertext[i + 1] = keyMatrix[r2][(c2 + 1) % 5];
                    }
                    else if (c1 == c2)
                    {
                        ciphertext[i] = keyMatrix[(r1 + 1) % 5][c1];
                        ciphertext[i + 1] = keyMatrix[(r2 + 1) % 5][c2];
                    }
                    else
                    {
                        ciphertext[i] = keyMatrix[r1][c2];
                        ciphertext[i + 1] = keyMatrix[r2][c1];
                    }
                }
                ciphertext[strlen(preparedText)] = '\0';
            }