#include <stdio.h>

int main() {
    for (int a = 1; a <= 9; a++) {
        for (int b = 1; b <= 9; b++) {
            if (b == a) continue;
            for (int c = 1; c <= 9; c++) {
                if (c == a || c == b) continue;
                int num1 = a * 100 + b * 10 + c;
                for (int d = 1; d <= 9; d++) {
                    if (d == a || d == b || d == c) continue;
                    for (int e = 1; e <= 9; e++) {
                        if (e == a || e == b || e == c || e == d) continue;
                        for (int f = 1; f <= 9; f++) {
                            if (f == a || f == b || f == c || f == d || f == e) continue;
                            int num2 = d * 100 + e * 10 + f;
                            if (num2 == 2 * num1) {
                                for (int g = 1; g <= 9; g++) {
                                    if (g == a || g == b || g == c || g == d || g == e || g == f) continue;
                                    for (int h = 1; h <= 9; h++) {
                                        if (h == a || h == b || h == c || h == d || h == e || h == f || h == g) continue;
                                        int num3 = g * 100 + h * 10 + i;
                                        if (num3 == 3 * num1 && num1 < num2 && num2 < num3) {
                                            printf("%d %d %d\n", num1, num2, num3);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}