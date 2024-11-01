#include <stdio.h>

int countDigit(int n, int x) {
    int count = 0;
    int factor = 1;
    int lower = 0, cur = 0, higher = 0;

    while (n / factor != 0) {
        lower = n - (n / factor) * factor;
        cur = (n / factor) % 10;
        higher = n / (factor * 10);

        if (cur == x) {
            count += higher * factor + lower + 1;
        } else if (cur < x) {
            count += higher * factor;
        } else {
            count += (higher + 1) * factor;
        }

        factor *= 10;
    }

    return count;
}

int main() {
    int n, x;
    scanf("%d %d", &n, &x);

    if (x == 0) {
        printf("%d\n", countDigit(n, x) - 1);
    } else {
        printf("%d\n", countDigit(n, x));
    }

    return 0;
}