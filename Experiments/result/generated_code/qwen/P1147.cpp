#include <stdio.h>

int main() {
    int M;
    scanf("%d", &M);

    for (int i = 1; i <= M / 2; i++) {
        int sum = 0;
        for (int j = i; sum < M; j++) {
            sum += j;
        }
        if (sum == M) {
            printf("%d %d\n", i, j - 1);
        }
    }

    return 0;
}