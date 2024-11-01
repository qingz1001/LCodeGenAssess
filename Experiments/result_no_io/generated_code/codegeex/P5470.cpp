#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

#define N 200005
#define M 1000005

struct Node {
    int x, y;
    ll val;
} c[N], d[N], e[M];

int n, k, l, cnt1, cnt2, cnt3;

int cmp1(const void *a, const void *b) {
    Node *aa = (Node *)a, *bb = (Node *)b;
    if (aa->val != bb->val) return aa->val < bb->val;
    return aa->x < bb->x;
}

int cmp2(const void *a, const void *b) {
    Node *aa = (Node *)a, *bb = (Node *)b;
    if (aa->val != bb->val) return aa->val < bb->val;
    return aa->y < bb->y;
}

int cmp3(const void *a, const void *b) {
    Node *aa = (Node *)a, *bb = (Node *)b;
    return aa->val > bb->val;
}

ll solve() {
    ll ans = 0;
    for (int i = 1; i <= k; i++) {
        ans += c[i].val + d[i].val;
    }
    for (int i = 1; i <= l; i++) {
        ans += e[i].val;
    }
    return ans;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d%d", &n, &k, &l);
        for (int i = 1; i <= n; i++) {
            scanf("%lld", &c[i].val);
            c[i].x = i;
        }
        for (int i = 1; i <= n; i++) {
            scanf("%lld", &d[i].val);
            d[i].y = i;
        }
        cnt1 = cnt2 = 0;
        for (int i = n; i >= 1; i--) {
            c[++cnt1] = c[i];
            d[++cnt2] = d[i];
        }
        cnt3 = 0;
        for (int i = 1; i <= n; i++) {
            e[++cnt3].val = c[i].val + d[i].val;
            e[cnt3].x = c[i].x;
            e[cnt3].y = d[i].y;
        }
        qsort(c + 1, cnt1, sizeof(Node), cmp1);
        qsort(d + 1, cnt2, sizeof(Node), cmp2);
        qsort(e + 1, cnt3, sizeof(Node), cmp3);
        ll ans = 0;
        for (int i = 0; i <= k - l; i++) {
            ans = solve();
        }
        printf("%lld\n", ans);
    }
    return 0;
}