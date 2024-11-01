#include <stdio.h>
#include <math.h>

int find_digit(int pos) {
    int n = 1;
    while (1) {
        long long triangular_number = (long long)n * (n + 1) / 2;
        if (triangular_number >= pos) {
            return (pos <= triangular_number - n + 1) ? 1 : 0;
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
        printf("%d\n", find_digit(A));
    }
    return 0;
}