#include <stdio.h>

int digitSum(long long n) {
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

int isRabbitNumber(long long n) {
    long long square = n * n;
    return digitSum(square) == digitSum(n) * digitSum(n);
}

int main() {
    long long L, R;
    scanf("%lld %lld", &L, &R);

    int count = 0;
    for (long long i = L; i <= R; i++) {
        if (isRabbitNumber(i)) {
            count++;
        }
    }

    printf("%d\n", count);

    return 0;
}