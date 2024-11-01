#include <stdio.h>

int main() {
    int n, i, j, sum;
    scanf("%d", &n);
    sum = 0;
    for (i = 1; i <= n; i++) {
        for (j = 1; j * j <= i; j++) {
            if (i % j == 0) {
                if (j * j == i) {
                    sum++;
                } else {
                    sum += 2;
                }
            }
        }
    }
    printf("%d\n", sum);
    return 0;
}