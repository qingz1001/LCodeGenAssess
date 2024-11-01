#include <stdio.h>
#include <string.h>

#define MAX_N 10

int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

int main() {
    int N;
    char X[MAX_N];
    int used[MAX_N] = {0};
    int result = 1;

    scanf("%d", &N);
    scanf("%s", X);

    for (int i = 0; i < N; i++) {
        int current = X[i] - '0';
        for (int j = 1; j < current; j++) {
            if (!used[j]) {
                result += factorial(N - i - 1);
            }
        }
        used[current] = 1;
    }

    printf("%d\n", result);

    return 0;
}