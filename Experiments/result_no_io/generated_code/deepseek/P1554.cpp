#include <stdio.h>

void countDigits(int num, int count[]) {
    while (num > 0) {
        count[num % 10]++;
        num /= 10;
    }
}

int main() {
    int M, N;
    scanf("%d %d", &M, &N);

    int count[10] = {0};
    for (int i = M; i <= N; i++) {
        countDigits(i, count);
    }

    for (int i = 0; i < 10; i++) {
        printf("%d ", count[i]);
    }
    printf("\n");

    return 0;
}