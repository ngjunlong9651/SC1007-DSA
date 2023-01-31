#include <stdio.h>
#include <stdlib.h>

int A5Q (int X, int N);

int main()
{
    printf("%d", A5Q(4,32));
}
int A5Q (int X, int N) {
    int HALF;

    if (N == 1) return X;
    else {
        HALF = N/2;
        if (2 * HALF == N) // N is even
            return A5Q(X, HALF) * A5Q(X, HALF);
        else
            return A5Q(X, HALF) * A5Q(X, HALF) * X;
    }
}
