#include <stdio.h>

int main() {
    int A, B, C;
    scanf("%d%d%d", &A, &B, &C);

    for (int a = 123; a <= 327; a++) {
        for (int b = a + 1; b <= 327; b++) {
            for (int c = b + 1; c <= 327; c++) {
                int a1 = a / 100, a2 = (a / 10) % 10, a3 = a % 10;
                int b1 = b / 100, b2 = (b / 10) % 10, b3 = b % 10;
                int c1 = c / 100, c2 = (c / 10) % 10, c3 = c % 10;
                if (a1 != a2 && a1 != a3 && a1 != b1 && a1 != b2 && a1 != b3 && a1 != c1 && a1 != c2 && a1 != c3 &&
                    a2 != a3 && a2 != b1 && a2 != b2 && a2 != b3 && a2 != c1 && a2 != c2 && a2 != c3 &&
                    a3 != b1 && a3 != b2 && a3 != b3 && a3 != c1 && a3 != c2 && a3 != c3 &&
                    b1 != b2 && b1 != b3 && b1 != c1 && b1 != c2 && b1 != c3 &&
                    b2 != b3 && b2 != c1 && b2 != c2 && b2 != c3 &&
                    b3 != c1 && b3 != c2 && b3 != c3) {
                    if (a * B == b * A && b * C == c * B) {
                        printf("%d %d %d\n", a, b, c);
                    }
                }
            }
        }
    }
    return 0;
}