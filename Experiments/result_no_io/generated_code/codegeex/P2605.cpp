#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

const int N = 20005;
const int INF = 0x3f3f3f3f;

int n, k;
int d[N], c[N], s[N], w[N];
int f[N][105];
int g[N];

struct Node {
    int d, w;
    bool operator < (const Node &a) const {
        return d < a.d;
    }
} a[N];

void init() {
    scanf("%d%d", &n, &k);
    for (int i = 2; i <= n; i++) {
        scanf("%d", &d[i]);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &c[i]);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &s[i]);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &w[i]);
    }
}

void solve() {
    for (int i = 1; i <= n; i++) {
        a[i] = {d[i], w[i]};
    }
    sort(a + 1, a + n + 1);
    memset(f, 0x3f, sizeof(f));
    memset(g, 0x3f, sizeof(g));
    f[0][0] = 0;
    g[0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < k; j++) {
            f[i][j] = min(f[i][j], f[i - 1][j] + c[i]);
            if (j) {
                f[i][j] = min(f[i][j], f[i - 1][j - 1] + c[i]);
            }
        }
        int p = lower_bound(a + 1, a + n + 1, (Node){d[i] - s[i], 0}) - a;
        for (int j = 0; j < k; j++) {
            f[i][j] = min(f[i][j], g[p] + c[i]);
        }
        for (int j = 1; j <= i; j++) {
            g[j] = min(g[j], f[i][0] - c[j]);
        }
    }
    int ans = INF;
    for (int i = 0; i < k; i++) {
        ans = min(ans, f[n][i]);
    }
    printf("%d\n", ans);
}

int main() {
    init();
    solve();
    return 0;
}