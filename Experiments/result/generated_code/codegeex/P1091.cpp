#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int heights[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &heights[i]);
    }

    int inc[n], dec[n];
    inc[0] = 1;
    for (int i = 1; i < n; i++) {
        inc[i] = 1;
        for (int j = 0; j < i; j++) {
            if (heights[i] > heights[j] && inc[i] < inc[j] + 1) {
                inc[i] = inc[j] + 1;
            }
        }
    }

    dec[n-1] = 1;
    for (int i = n-2; i >= 0; i--) {
        dec[i] = 1;
        for (int j = n-1; j > i; j--) {
            if (heights[i] > heights[j] && dec[i] < dec[j] + 1) {
                dec[i] = dec[j] + 1;
            }
        }
    }

    int max = 0;
    for (int i = 0; i < n; i++) {
        if (inc[i] + dec[i] - 1 > max) {
            max = inc[i] + dec[i] - 1;
        }
    }

    printf("%d\n", n - max);
    return 0;
}