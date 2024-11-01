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
    int used[10] = {0};

    for (int i = 0; i < N; i++) {
        int digit = X[i] - '0';
        int smaller = 0;
        for (int j = 1; j < digit; j++) {
            if (!used[j]) {
                smaller++;
            }
        }
        rank += smaller * factorial(N - i - 1);
        used[digit] = 1;
    }

    printf("%d\n", rank + 1);

    return 0;
}