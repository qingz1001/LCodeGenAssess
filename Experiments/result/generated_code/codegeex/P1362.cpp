#include <stdio.h>

int sum(int n) {
    int s = 0;
    while (n > 0) {
        s += n % 10;
        n /= 10;
    }
    return s;
}

int isRabbitNumber(int x) {
    return sum(x * x) == sum(x) * sum(x);
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