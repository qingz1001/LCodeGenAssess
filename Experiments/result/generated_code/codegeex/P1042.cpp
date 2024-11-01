#include <stdio.h>

int main() {
    char ch;
    int a = 0, b = 0, c = 0, d = 0, e = 0, f = 0;
    int win1 = 0, win2 = 0;

    while ((ch = getchar()) != 'E') {
        if (ch == 'W') {
            a++;
        } else if (ch == 'L') {
            b++;
        }

        // 11分制
        if (a - b >= 2 || b - a >= 2) {
            if (win1 == 0) {
                printf("%d:%d\n", a, b);
                win1 = 1;
            } else {
                if (a > b) {
                    c++;
                } else {
                    d++;
                }
                printf("%d:%d\n", c, d);
                a = 0;
                b = 0;
                win1 = 0;
            }
        }

        // 21分制
        if ((a >= 11 && a - b >= 2) || (b >= 11 && b - a >= 2)) {
            if (win2 == 0) {
                printf("%d:%d\n", a, b);
                win2 = 1;
            } else {
                if (a > b) {
                    e++;
                } else {
                    f++;
                }
                printf("%d:%d\n", e, f);
                a = 0;
                b = 0;
                win2 = 0;
            }
        }
    }

    return 0;
}