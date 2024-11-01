#include <stdio.h>

int main() {
    int a, b, c;
    for (a = 192; a <= 576; a++) {
        for (b = a * 2; b <= a * 3 && b <= 576; b++) {
            c = a * 3;
            if (c == b * 2) {
                printf("%d %d %d\n", a, b, c);
            }
        }
    }
    return 0;
}