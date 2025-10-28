#include <stdio.h>

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

// S-box lookup with 6-bit input converted to 4-bit output
int s_box_lookup(int s_box[4][16], int input_val)
{
    // Row: outer bits (b5, b0), Column: middle four bits (b4-b1)
    int row = ((input_val >> 5) & 1) * 2 + (input_val & 1);
    int col = (input_val >> 1) & 0x0F;

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