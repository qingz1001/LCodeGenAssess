#include <stdio.h>

int sumOfDigits(int n) {
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

int isRabbitNumber(int x) {
    int sx = sumOfDigits(x);
    int sxx = sumOfDigits(x * x);
    return sxx == sx * sx;
}

int main() {
    int L, R;
    scanf("%d %d", &L, &R);
    int count = 0;
    for (int i = L; i <= R; i++) {
        if (isRabbitNumber(i)) {
            count++;
        }
    }
    printf("%d\n", count);
    return 0;
}