#include <stdio.h>

int main() {
    long long M, N;
    scanf("%lld %lld", &M, &N);

    int count[10] = {0};

    for (long long i = M; i <= N; i++) {
        long long num = i;
        while (num > 0) {
            int digit = num % 10;
            count[digit]++;
            num /= 10;
        }
    }

    for (int i = 0; i < 10; i++) {
        printf("%d ", count[i]);
    }
    printf("\n");

    return 0;
}