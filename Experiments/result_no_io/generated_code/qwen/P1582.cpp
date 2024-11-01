#include <stdio.h>

int main() {
    long long N, K;
    scanf("%lld %lld", &N, &K);

    if (N <= K) {
        printf("0\n");
        return 0;
    }

    long long bottles = N - K;
    long long new_bottles = 0;

    while (bottles > 0) {
        if (bottles >= 2) {
            bottles -= 2;
            new_bottles++;
        } else {
            break;
        }
    }

    printf("%lld\n", new_bottles);
    return 0;
}