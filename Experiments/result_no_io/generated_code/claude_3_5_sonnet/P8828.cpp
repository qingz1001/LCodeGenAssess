#include <stdio.h>
#include <math.h>

int main() {
    int c;
    scanf("%d", &c);

    for (int a = 1; a <= c; a++) {
        for (int b = a; b <= c; b++) {
            if (a * a + b * b == c * c) {
                printf("%d %d\n", a, b);
                return 0;
            }
        }
    }

    return 0;
}