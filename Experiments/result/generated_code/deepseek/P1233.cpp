#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int length;
    int width;
} Stick;

int compare(const void *a, const void *b) {
    Stick *stickA = (Stick *)a;
    Stick *stickB = (Stick *)b;
    if (stickA->length == stickB->length) {
        return stickB->width - stickA->width;
    }
    return stickB->length - stickA->length;
}

int minPrepareTime(int n, Stick sticks[]) {
    qsort(sticks, n, sizeof(Stick), compare);

    int dp[5000];
    int max_dp = 0;

    for (int i = 0; i < n; i++) {
        dp[i] = 1;
        for (int j = 0; j < i; j++) {
            if (sticks[i].length <= sticks[j].length && sticks[i].width <= sticks[j].width) {
                dp[i] = dp[j] + 1;
                break;
            }
        }
        if (dp[i] > max_dp) {
            max_dp = dp[i];
        }
    }

    return n - max_dp;
}

int main() {
    int n;
    scanf("%d", &n);
    Stick sticks[5000];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &sticks[i].length, &sticks[i].width);
    }

    int result = minPrepareTime(n, sticks);
    printf("%d\n", result);

    return 0;
}