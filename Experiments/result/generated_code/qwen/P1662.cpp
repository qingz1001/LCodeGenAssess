#include <stdio.h>

int main() {
    int X;
    scanf("%d", &X);

    int n = 1337;
    int direction = 1;

    while (n != X) {
        if (n % 7 == 0 || contains_seven(n)) {
            direction *= -1;
        }
        n += direction;
        if (n <= 0) {
            n = 1337 + n % 1337;
        } else if (n > 1337) {
            n %= 1337;
        }
    }

    printf("%d\n", n);
    return 0;
}

int contains_seven(int num) {
    while (num > 0) {
        if (num % 10 == 7) {
            return 1;
        }
        num /= 10;
    }
    return 0;
}