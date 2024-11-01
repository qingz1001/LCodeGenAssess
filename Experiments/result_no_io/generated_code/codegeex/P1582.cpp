#include <stdio.h>

int main() {
    long long N, K;
    scanf("%lld %lld", &N, &K);

    if (N <= K) {
        printf("0\n");
        return 0;
    }

    long long new_bottles = 0;
    long long current_bottles = N;

    while (current_bottles > K) {
        long long full_bottles = current_bottles / 2;
        long long remaining_bottles = current_bottles % 2;
        new_bottles += remaining_bottles;
        current_bottles = full_bottles;
    }

    printf("%lld\n", new_bottles);
    return 0;
}