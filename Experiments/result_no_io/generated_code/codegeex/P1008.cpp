#include <stdio.h>

int main() {
    int a, b, c;
    for (a = 100; a <= 333; a++) {
        for (b = 100; b <= 666; b++) {
            c = 2 * b - a;
            if (c >= 100 && c <= 999) {
                printf("%d %d %d\n", a, b, c);
            }
        }
    }
    return 0;
}