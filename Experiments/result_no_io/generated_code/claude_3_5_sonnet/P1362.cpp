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
    int s_n = digitSum(n);
    int s_n_squared = digitSum(n * n);
    return s_n_squared == s_n * s_n;
}

int countRabbitNumbers(long long L, long long R) {
    int count = 0;
    for (long long i = L; i <= R; i++) {
        if (isRabbitNumber(i)) {
            count++;
        }
    }
    return count;
}

int main() {
    long long L, R;
    scanf("%lld %lld", &L, &R);
    
    int result = countRabbitNumbers(L, R);
    printf("%d\n", result);
    
    return 0;
}