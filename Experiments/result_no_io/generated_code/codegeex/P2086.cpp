#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXN 500005
#define MAXM 500005
#define MAXQ 100005

typedef long long ll;

int n, m, x, y, T;
ll a[MAXN][MAXM], sum[MAXN][MAXM], f[MAXN][MAXM];
int st[MAXN], top, q[MAXQ], hd, tl;
ll tag[MAXN], s[MAXM], t[MAXM];

void update(int l, int r, ll v) {
    int i;
    for (i = l; i <= m; i += i & -i) s[i] += v;
    for (i = r + 1; i <= m; i += i & -i) s[i] -= v;
}

ll query(int p) {
    ll res = 0;
    for (; p; p -= p & -p) res += s[p];
    return res;
}

void update2(int l, int r, ll v) {
    int i;
    for (i = l; i <= n; i += i & -i) t[i] += v;
    for (i = r + 1; i <= n; i += i & -i) t[i] -= v;
}

ll query2(int p) {
    ll res = 0;
    for (; p; p -= p & -p) res += t[p];
    return res;
}

void add(int p, ll v) {
    int i;
    for (i = p; i <= m; i += i & -i) f[p][i] += v;
}

ll find(int p) {
    int i, l, r;
    ll mid, v;
    for (i = m; i; i -= i & -i) {
        if (f[p][i]) {
            l = 1;
            r = i;
            while (l < r) {
                mid = (l + r) >> 1;
                if (f[p][mid]) r = mid;
                else l = mid + 1;
            }
            v = (ll)mid * query(p);
            if (v > a[p][i]) return v;
        }
    }
    return 0;
}

int main() {
    int i, j, l, r, op, x1, y1, x2, y2;
    ll v, c, ans;
    scanf("%d%d%d%d%d", &n, &m, &x, &y, &T);
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            scanf("%lld", &a[i][j]);
            sum[i][j] = sum[i][j - 1] + a[i][j];
            add(j, a[i][j]);
        }
    }
    for (i = 1; i <= m; i++) {
        st[top = 1] = 1;
        for (j = 2; j <= n; j++) {
            while (top > 1 && a[j][i] < a[st[top - 1]][i]) top--;
            f[j][i] = f[st[top]][i] + a[j][i] * (j - st[top]);
            st[++top] = j;
        }
    }
    while (T--) {
        scanf("%d", &op);
        if (op == 0) {
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            l = y - y1;
            r = y + y2;
            c = (ll)x1 * query2(x) - sum[x - x1][r] + sum[x - x1][l - 1];
            c += (ll)(x2 - x1) * query(r) - sum[x + x2][r] + sum[x + x2][l - 1];
            c += find(x);
            printf("%lld\n", ans = c / (x2 - x1 + 1) / (y2 - y1 + 1));
        } else {
            scanf("%d%d%d%lld", &x1, &y1, &x2, &c);
            l = y - y1;
            r = y + x2;
            update(l, r, c);
            update2(x1, x2, c);
        }
    }
    return 0;
}