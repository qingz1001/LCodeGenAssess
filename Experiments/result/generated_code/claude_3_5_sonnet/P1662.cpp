#include <stdio.h>
#include <stdbool.h>

#define N 1337

bool containsSeven(int num) {
    while (num > 0) {
        if (num % 10 == 7) return true;
        num /= 10;
    }
    return false;
}

int main() {
    int X;
    scanf("%d", &X);

    int current = 1;
    int direction = 1;
    int count = 1;

    while (count < X) {
        if (count % 7 == 0 || containsSeven(count)) {
            direction = -direction;
        }
        current += direction;
        if (current > N) current = 1;
        if (current < 1) current = N;
        count++;
    }

    printf("%d\n", current);

    return 0;
}