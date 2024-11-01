#include <stdio.h>

void countDigits(long long start, long long end, int counts[10]) {
    for (long long i = start; i <= end; i++) {
        long long num = i;
        while (num > 0) {
            counts[num % 10]++;
            num /= 10;
        }
    }
}

int main() {
    long long M, N;
    int counts[10] = {0};

    scanf("%lld %lld", &M, &N);

    countDigits(M, N, counts);

    for (int i = 0; i < 10; i++) {
        printf("%d", counts[i]);
        if (i < 9) {
            printf(" ");
        }
    }
    printf("\n");

    return 0;
}