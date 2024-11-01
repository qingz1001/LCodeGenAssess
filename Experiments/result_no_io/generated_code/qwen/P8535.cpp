#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int result = 0;

    while (n >= 1) {
        if (n >= 8) {
            result += 1;
            n -= 8;
        } else if (n >= 7) {
            result += 2;
            n -= 7;
        } else if (n >= 6) {
            result += 3;
            n -= 6;
        } else if (n >= 5) {
            result += 4;
            n -= 5;
        } else if (n >= 4) {
            result += 5;
            n -= 4;
        } else if (n >= 3) {
            result += 6;
            n -= 3;
        } else if (n >= 2) {
            result += 7;
            n -= 2;
        } else if (n == 1) {
            result += 8;
            n -= 1;
        }
    }

    printf("%d\n", result);
    return 0;
}