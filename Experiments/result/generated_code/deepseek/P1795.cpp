#include <stdio.h>
#include <math.h>

int get_digit(int pos) {
    int n = 1;
    while (1) {
        long long triangular = (long long)n * (n + 1) / 2;
        if (triangular >= pos) {
            return (pos <= triangular - n) ? 0 : 1;
        }
        n++;
    }
}

int main() {
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        int A;
        scanf("%d", &A);
        printf("%d\n", get_digit(A));
    }
    return 0;
}