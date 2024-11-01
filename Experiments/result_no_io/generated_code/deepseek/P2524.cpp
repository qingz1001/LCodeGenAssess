#include <stdio.h>
#include <string.h>

int factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main() {
    int N;
    char X[10];
    scanf("%d", &N);
    scanf("%s", X);

    int rank = 0;
    int factorials[10];
    for (int i = 0; i < N; i++) {
        factorials[i] = factorial(N - i - 1);
    }

    for (int i = 0; i < N; i++) {
        int count = 0;
        for (int j = i + 1; j < N; j++) {
            if (X[j] < X[i]) {
                count++;
            }
        }
        rank += count * factorials[i];
    }

    printf("%d\n", rank + 1);
    return 0;
}