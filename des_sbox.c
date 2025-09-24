#include <stdio.h>

/**
 * C Code to Demonstrate DES S-Box Lookup
 * * This program calculates the output of DES S-boxes 1 and 2
 * for given 6-bit inputs.
 */

// DES S-box 1 (S_1)
int s1[4][16] = {
    {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
    {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
    {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
    {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}};

// DES S-box 2 (S_2)
int s2[4][16] = {
    {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
    {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
    {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
    {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}};

/**
 * @brief Performs a lookup in a given DES S-box.
 * * @param s_box The S-box table (a 4x16 2D array).
 * @param input_val A decimal integer (0-63) representing the 6-bit input.
 * @return The 4-bit output value from the S-box.
 */
int s_box_lookup(int s_box[4][16], int input_val)
{
    // The input_val is a 6-bit number (e.g., b5 b4 b3 b2 b1 b0)

    // The row is determined by the outer bits: b5 and b0.
    // We combine them to form a 2-bit number.
    // `(input_val >> 5) & 1` isolates the most significant bit (b5).
    // `(input_val & 1)` isolates the least significant bit (b0).
    int row = ((input_val >> 5) & 1) * 2 + (input_val & 1);

    // The column is determined by the middle four bits: b4 b3 b2 b1.
    // `(input_val >> 1)` shifts the middle bits to the rightmost positions.
    // `& 0x0F` (which is 15 or binary 1111) masks them to get the column value.
    int col = (input_val >> 1) & 0x0F;

    // Return the value from the S-box table at the calculated row and column.
    return s_box[row][col];
}

int main()
{
    // The specific inputs from your question
    int input1 = 59;
    int input2 = 23;

    // Perform the lookups using the function
    int output1 = s_box_lookup(s1, input1);
    int output2 = s_box_lookup(s2, input2);

    // Print the final results to the console
    printf("Calculating DES S-box outputs...\n");
    printf("----------------------------------\n");
    printf("S_1(%d) = %d\n", input1, output1);
    printf("S_2(%d) = %d\n", input2, output2);
    printf("----------------------------------\n");

    return 0;
}