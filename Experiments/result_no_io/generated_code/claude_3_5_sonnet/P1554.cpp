#include <stdio.h>
#include <string.h>

void countDigits(int m, int n, int *counts) {
    for (int i = m; i <= n; i++) {
        int num = i;
        while (num > 0) {
            counts[num % 10]++;
            num /= 10;
        }
    }
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    int counts[10] = {0};
    countDigits(m, n, counts);

    for (int i = 0; i < 10; i++) {
        printf("%d ", counts[i]);
    }
    printf("\n");

    return 0;
}