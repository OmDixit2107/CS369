#include <stdio.h>
#include <string.h> // Required for strlen()

// Use a 64-bit integer type to prevent overflow with intermediate results
typedef unsigned long long poly_t;

// --- Function Prototypes ---
int degree(poly_t poly);
void print_poly(poly_t poly);
poly_t poly_multiply(poly_t a, poly_t b);
poly_t poly_inverse(poly_t g, poly_t m);
poly_t binary_string_to_poly(const char *bin_str);

poly_t binary_string_to_poly(const char *bin_str)
{
    poly_t result = 0;
    int len = strlen(bin_str);
    for (int i = 0; i < len; i++)
    {
        // Left shift the result to make room for the next bit
        result <<= 1;
        if (bin_str[i] == '1')
        {
            result |= 1;
        }
        else if (bin_str[i] != '0')
        {
            // Basic error handling for invalid characters
            printf("Error: Invalid character '%c' in binary string.\n", bin_str[i]);
            return 0; // Return 0 on error
        }
    }
    return result;
}

int degree(poly_t poly)
{
    int d = 0;
    if (poly == 0)
        return -1;
    // Keep shifting right until the number is 0, counting the shifts
    poly_t temp = poly;
    while ((temp >>= 1) != 0)
    {
        d++;
    }
    return d;
}

/**
 * @brief Prints a polynomial in a human-readable format (e.g., x^2 + 1).
 * @param poly The polynomial to print.
 */
void print_poly(poly_t poly)
{
    if (poly == 0)
    {
        printf("0");
        return;
    }
    int d = degree(poly);
    int is_first_term = 1;
    for (int i = d; i >= 0; i--)
    {
        if ((poly >> i) & 1)
        { // Check if the i-th bit is set
            if (!is_first_term)
            {
                printf(" + ");
            }
            if (i > 1)
            {
                printf("x^%d", i);
            }
            else if (i == 1)
            {
                printf("x");
            }
            else
            {
                printf("1");
            }
            is_first_term = 0;
        }
    }
}

poly_t poly_multiply(poly_t a, poly_t b)
{
    poly_t result = 0;
    for (int i = 0; i <= degree(b); i++)
    {
        if ((b >> i) & 1)
        {
            result ^= (a << i);
        }
    }
    return result;
}

/**
 * @brief Finds the multiplicative inverse of g(x) modulo m(x).
 * @param g The polynomial to invert.
 * @param m The irreducible modulus polynomial defining the field.
 * @return The multiplicative inverse, or -1 if no inverse exists.
 */
poly_t poly_inverse(poly_t g, poly_t m)
{
    poly_t r_prev = m;
    poly_t r_curr = g;
    poly_t s_prev = 0;
    poly_t s_curr = 1;

    while (r_curr != 0)
    {
        poly_t q = 0;
        poly_t temp_r = r_prev;

        // Polynomial long division to find q = r_prev / r_curr
        while (degree(temp_r) >= degree(r_curr))
        {
            int d = degree(temp_r) - degree(r_curr);
            q ^= (1ULL << d); // Use 1ULL for unsigned long long
            temp_r ^= (r_curr << d);
        }

        // Update remainders
        poly_t r_next = temp_r;
        r_prev = r_curr;
        r_curr = r_next;

        // Update s-coefficients
        poly_t s_next = s_prev ^ poly_multiply(q, s_curr);
        s_prev = s_curr;
        s_curr = s_next;
    }

    if (r_prev != 1)
    {
        return -1;
    }

    return s_prev;
}

int main()
{

    // m(x) is the irreducible polynomial for the field.
    // For AES, this is x^8 + x^4 + x^3 + x + 1.
    const char *m_str = "100011011";

    // g(x) is the polynomial you want to find the inverse of.
    const char *g_str = "00001100";

    // Convert the defined strings to polynomial integers
    poly_t m = binary_string_to_poly(m_str);
    poly_t g = binary_string_to_poly(g_str);

    printf("Field defined by m(x) = ");
    print_poly(m);
    printf(" (0x%llX)\n", m);

    printf("Finding inverse of g(x) = ");
    print_poly(g);
    printf(" (0x%llX)\n\n", g);

    poly_t inverse = poly_inverse(g, m);

    if (inverse != -1)
    {
        printf("✅ The multiplicative inverse is:\n");
        print_poly(inverse);
        printf(" (0x%llX)\n", inverse);
    }
    else
    {
        printf("❌ No multiplicative inverse exists.\n");
    }

    return 0;
}