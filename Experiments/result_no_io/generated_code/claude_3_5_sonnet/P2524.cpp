#include <stdio.h>
#include <string.h>

#define MAX_N 10

int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

int main() {
    int N, X[MAX_N], used[MAX_N] = {0};
    int result = 1;
    char input[MAX_N];

    scanf("%d", &N);
    scanf("%s", input);

    for (int i = 0; i < N; i++) {
        X[i] = input[i] - '0';
    }

    for (int i = 0; i < N; i++) {
        int count = 0;
        for (int j = 1; j < X[i]; j++) {
            if (!used[j]) count++;
        }
        result += count * factorial(N - i - 1);
        used[X[i]] = 1;
    }

    printf("%d\n", result);

    return 0;
}