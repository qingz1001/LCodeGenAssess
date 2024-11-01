#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100005

int n, m, p;
int T[MAXN];
int lastAns = 0;

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int solve() {
    int ans = INT_MAX;
    for (int i = 0; i < n; i++) {
        int maxT = 0;
        for (int j = 0; j < n; j++) {
            maxT = max(maxT, T[(i + j) % n] - j);
        }
        ans = min(ans, maxT + n);
    }
    return ans;
}

int main() {
    scanf("%d %d %d", &n, &m, &p);
    for (int i = 0; i < n; i++) {
        scanf("%d", &T[i]);
    }

    lastAns = solve();
    printf("%d\n", lastAns);

    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        if (p == 1) {
            x ^= lastAns;
            y ^= lastAns;
        }
        T[x] = y;
        lastAns = solve();
        printf("%d\n", lastAns);
    }

    return 0;
}