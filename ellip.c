#include <stdio.h>

// Structure to represent a point (x, y)
typedef struct
{
    int x, y;
    int is_infinity; // 1 if point at infinity
} Point;

// Compute (a mod m) correctly even for negative a
int mod(int a, int m)
{
    int res = a % m;
    if (res < 0)
        res += m;
    return res;
}

// Compute modular inverse of a mod p using Extended Euclidean Algorithm
int modInverse(int a, int p)
{
    int t = 0, newt = 1;
    int r = p, newr = a;
    while (newr != 0)
    {
        int quotient = r / newr;
        int temp = newt;
        newt = t - quotient * newt;
        t = temp;

        temp = newr;
        newr = r - quotient * newr;
        r = temp;
    }
    if (r > 1)
    {
        printf("No modular inverse for %d mod %d\n", a, p);
        return -1;
    }
    if (t < 0)
        t += p;
    return t;
}

// Point addition on elliptic curve: y^2 = x^3 + a*x + b (mod p)
Point addPoints(Point P, Point Q, int a, int p)
{
    Point R;

    // Handle special cases
    if (P.is_infinity)
        return Q;
    if (Q.is_infinity)
        return P;

    // If P == -Q, result is infinity
    if (P.x == Q.x && mod(P.y + Q.y, p) == 0)
    {
        R.is_infinity = 1;
        return R;
    }

    int lambda;
    if (P.x == Q.x && P.y == Q.y)
    {
        // Point doubling
        int numerator = mod(3 * P.x * P.x + a, p);
        int denominator = modInverse(mod(2 * P.y, p), p);
        lambda = mod(numerator * denominator, p);
    }
    else
    {
        // Regular addition
        int numerator = mod(Q.y - P.y, p);
        int denominator = modInverse(mod(Q.x - P.x, p), p);
        lambda = mod(numerator * denominator, p);
    }

    int x3 = mod(lambda * lambda - P.x - Q.x, p);
    int y3 = mod(lambda * (P.x - x3) - P.y, p);

    R.x = x3;
    R.y = y3;
    R.is_infinity = 0;
    return R;
}

// Scalar multiplication using double-and-add method
Point scalarMult(int k, Point P, int a, int p)
{
    Point R = {0, 0, 1}; // Point at infinity
    Point Q = P;

    while (k > 0)
    {
        if (k & 1)
            R = addPoints(R, Q, a, p);
        Q = addPoints(Q, Q, a, p);
        k >>= 1;
    }
    return R;
}

int main()
{
    // Example curve: y^2 = x^3 + 7x + 2 mod 17
    int a = 7, b = 2, p = 11;

    Point P = {8, 3, 0};
    Point Q = {10, 7, 0};

    printf("Elliptic curve: y^2 = x^3 + %dx + %d (mod %d)\n", a, b, p);
    printf("P = (%d, %d)\n", P.x, P.y);
    printf("Q = (%d, %d)\n", Q.x, Q.y);

    Point R = addPoints(P, Q, a, p);
    if (!R.is_infinity)
        printf("P + Q = (%d, %d)\n", R.x, R.y);
    else
        printf("P + Q = Point at infinity\n");

    Point doubleP = addPoints(P, P, a, p);
    printf("2P = (%d, %d)\n", doubleP.x, doubleP.y);

    Point sevenP = scalarMult(7, P, a, p);
    printf("7P = (%d, %d)\n", sevenP.x, sevenP.y);

    return 0;
}
