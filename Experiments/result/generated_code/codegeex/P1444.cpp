#include <stdio.h>

int n, x[15], y[15], pair[15], next[15];

int check() {
    for (int start = 1; start <= n; start++) {
        int pos = start;
        for (int count = 0; count < n; count++) {
            pos = next[pair[pos]];
        }
        if (pos != -1) {
            return 1;
        }
    }
    return 0;
}

int solve() {
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (pair[i] == 0 && pair[j] == 0) {
                pair[i] = j;
                pair[j] = i;
                if (solve() == 0) {
                    ans += check();
                }
                pair[i] = pair[j] = 0;
            }
        }
    }
    return ans;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &x[i], &y[i]);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (y[i] == y[j] && x[j] > x[i]) {
                if (next[i] == 0 || x[j] - x[i] < x[next[i]] - x[i]) {
                    next[i] = j;
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        next[i] = next[next[i]];
    }
    printf("%d\n", solve());
    return 0;
}