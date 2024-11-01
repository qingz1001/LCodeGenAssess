#include <stdio.h>
#include <algorithm>
using namespace std;

const int N = 100005;
typedef long long ll;

struct node {
    int l, r, val;
} a[N * 4];

int n, q;
ll s[N], a_[N];

void build(int x, int l, int r) {
    a[x].l = l;
    a[x].r = r;
    if (l == r) {
        a[x].val = a_[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(x << 1, l, mid);
    build(x << 1 | 1, mid + 1, r);
    a[x].val = max(a[x << 1].val, a[x << 1 | 1].val);
}

void update(int x, int pos, ll val) {
    if (a[x].l == a[x].r) {
        a[x].val = val;
        return;
    }
    int mid = (a[x].l + a[x].r) >> 1;
    if (pos <= mid) update(x << 1, pos, val);
    else update(x << 1 | 1, pos, val);
    a[x].val = max(a[x << 1].val, a[x << 1 | 1].val);
}

ll query(int x, int l, int r) {
    if (a[x].l >= l && a[x].r <= r) return a[x].val;
    int mid = (a[x].l + a[x].r) >> 1;
    ll ans = -1e18;
    if (l <= mid) ans = max(ans, query(x << 1, l, r));
    if (r > mid) ans = max(ans, query(x << 1 | 1, l, r));
    return ans;
}

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a_[i]);
        s[i] = s[i - 1] + a_[i];
    }
    build(1, 1, n);
    for (int i = 0; i < q; i++) {
        int op, l, r;
        scanf("%d%d%d", &op, &l, &r);
        if (op == 0) {
            ll x;
            scanf("%lld", &x);
            update(1, l, max(a_[l], x));
            a_[l] = max(a_[l], x);
        } else {
            printf("%lld\n", query(1, l, r) + s[r] - s[l - 1]);
        }
    }
    return 0;
}