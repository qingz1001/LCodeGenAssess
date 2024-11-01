#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100005

int a[MAX_N], b[MAX_N];

int max(int a, int b) {
    return a > b ? a : b;
}

void solve() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }

    int maxLen = 0, start = -1, end = -1;
    int curLen = 0, curStart = -1;

    for (int i = 0; i < n; i++) {
        if (a[i] == 1) {
            if (curStart == -1) curStart = i;
            curLen++;
        } else {
            if (curLen > maxLen) {
                maxLen = curLen;
                start = curStart;
                end = i - 1;
            }
            curLen = 0;
            curStart = -1;
        }
    }

    if (curLen > maxLen) {
        maxLen = curLen;
        start = curStart;
        end = n - 1;
    }

    if (maxLen == 0) {
        printf("0\n");
        for (int i = 0; i < n; i++) {
            printf("%d ", a[i]);
        }
        printf("\n");
        return;
    }

    int left = start > 0 ? start - 1 : -1;
    int right = end < n - 1 ? end + 1 : n;

    int bestLeft = left, bestRight = right;
    int bestScore = maxLen;

    for (int l = left; l >= 0; l--) {
        for (int r = right; r < n; r++) {
            int score = (r - l + 1) - (r - end) - (start - l);
            if (score > bestScore) {
                bestScore = score;
                bestLeft = l;
                bestRight = r;
            }
        }
    }

    printf("%d\n", bestScore);
    for (int i = bestLeft; i <= bestRight; i++) {
        b[i] = 1;
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", b[i]);
    }
    printf("\n");
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}