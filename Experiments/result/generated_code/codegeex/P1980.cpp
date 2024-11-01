#include <stdio.h>

int main() {
    int n, x, count = 0;
    scanf("%d %d", &n, &x);

    for (int i = 1; i <= n; i++) {
        int num = i;
        while (num > 0) {
            if (num % 10 == x) {
                count++;
            }
            num /= 10;
        }
    }

    printf("%d\n", count);
    return 0;
}