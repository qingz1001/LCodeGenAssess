#include <stdio.h>

int contains_seven(int num) {
    while (num > 0) {
        if (num % 10 == 7) return 1;
        num /= 10;
    }
    return 0;
}

int main() {
    int X;
    scanf("%d", &X);

    int direction = 1; // 1 for forward, -1 for backward
    int current_person = 1;

    for (int i = 1; i <= X; i++) {
        if (i % 7 == 0 || contains_seven(i)) {
            direction *= -1;
        }

        if (direction == 1) {
            current_person = (current_person % 1337) + 1;
        } else {
            current_person = ((current_person - 2 + 1337) % 1337) + 1;
        }
    }

    printf("%d\n", current_person);
    return 0;
}