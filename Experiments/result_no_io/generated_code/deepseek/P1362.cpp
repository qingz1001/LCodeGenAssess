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
    int sx2 = sumOfDigits(x * x);
    return sx2 == sx * sx;
}

int countRabbitNumbers(int L, int R) {
    int count = 0;
    for (int i = L; i <= R; i++) {
        if (isRabbitNumber(i)) {
            count++;
        }
    }
    return count;
}

int main() {
    int L, R;
    scanf("%d %d", &L, &R);
    printf("%d\n", countRabbitNumbers(L, R));
    return 0;
}