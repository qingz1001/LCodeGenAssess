#include <stdio.h>
#include <stdbool.h>

bool is_seven(int num) {
    while (num > 0) {
        if (num % 10 == 7) {
            return true;
        }
        num /= 10;
    }
    return false;
}

int main() {
    int X;
    scanf("%d", &X);

    int current = 1;
    int direction = 1;
    for (int i = 1; i <= X; i++) {
        if (i % 7 == 0 || is_seven(i)) {
            direction = -direction;
        }
        current += direction;
        if (current > 1337) {
            current = 1;
        } else if (current < 1) {
            current = 1337;
        }
    }

    printf("%d\n", current);
    return 0;
}