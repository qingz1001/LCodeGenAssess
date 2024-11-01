#include <stdio.h>
#include <string.h>

#define MAX_N 100005

int n, m, K;
int trans[MAX_N][20], fail[MAX_N], last[MAX_N];
int q[MAX_N], head, tail;

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

int lcm(int a, int b) {
    return a / gcd(a, b) * b;
}

void build() {
    int i, j, u, v;
    for (i = 0; i < m; i++) {
        if (i == 0) {
            for (j = 0; j < m; j++)
                trans[0][j] = 1;
        } else {
            for (j = 0; j < m; j++)
                trans[i][j] = i * m + j;
        }
    }
    fail[1] = 0;
    head = tail = 0;
    q[tail++] = 1;
    while (head < tail) {
        u = q[head++];
        for (i = 0; i < m; i++) {
            v = trans[fail[u]][i];
            if (!fail[trans[u][i]]) {
                fail[trans[u][i]] = v;
                q[tail++] = trans[u][i];
            }
        }
    }
    for (i = 1; i < n; i++) {
        last[i] = 0;
        if (i % K == 0)
            last[i] = i;
    }
    for (i = 1; i < n; i++) {
        u = last[fail[i]];
        while (u && !last[i]) {
            if ((long long)u * m % K == i % K)
                last[i] = i;
            u = last[fail[u]];
        }
    }
}

int solve() {
    int i, j, u;
    n = K * m;
    build();
    for (i = 1; i < n; i++) {
        if (last[i] == 0)
            return i;
    }
    return n;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &m, &K);
        if (m == 1) {
            printf("%d\n", K);
        } else {
            int ans = solve();
            if (ans == K * m)
                printf("-1\n");
            else
                printf("%d\n", ans);
        }
    }
    return 0;
}