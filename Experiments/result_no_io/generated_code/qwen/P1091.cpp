#include <stdio.h>
#include <stdlib.h>

#define MAXN 100

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main() {
    int n, i, j;
    scanf("%d", &n);
    int heights[MAXN];
    for (i = 0; i < n; i++) {
        scanf("%d", &heights[i]);
    }

    int dp_inc[MAXN], dp_dec[MAXN];
    for (i = 0; i < n; i++) {
        dp_inc[i] = 1;
        dp_dec[i] = 1;
    }

    for (i = 1; i < n; i++) {
        for (j = 0; j < i; j++) {
            if (heights[i] > heights[j]) {
                dp_inc[i] = max(dp_inc[i], dp_inc[j] + 1);
            }
        }
    }

    for (i = n - 2; i >= 0; i--) {
        for (j = n - 1; j > i; j--) {
            if (heights[i] > heights[j]) {
                dp_dec[i] = max(dp_dec[i], dp_dec[j] + 1);
            }
        }
    }

    int max_length = 0;
    for (i = 0; i < n; i++) {
        max_length = max(max_length, dp_inc[i] + dp_dec[i] - 1);
    }

    printf("%d\n", n - max_length);

    return 0;
}