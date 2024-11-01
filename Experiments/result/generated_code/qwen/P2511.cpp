#include <stdio.h>
#include <stdlib.h>

#define MOD 10007

int n, m;
int lengths[50001];

int canCut(int maxLen) {
    int cuts = 0;
    for (int i = 1; i <= n - 1; i++) {
        if (lengths[i] > maxLen) {
            cuts += (lengths[i] - 1) / maxLen;
        }
    }
    return cuts <= m;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &lengths[i]);
    }

    int left = 0, right = 0;
    for (int i = 1; i <= n; i++) {
        right += lengths[i];
    }

    while (left < right) {
        int mid = left + (right - left) / 2;
        if (canCut(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    int count = 0;
    for (int i = 1; i <= n - 1; i++) {
        if (lengths[i] > left) {
            count++;
        }
    }

    printf("%d %d\n", left, count % MOD);

    return 0;
}