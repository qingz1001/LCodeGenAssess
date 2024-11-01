#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

typedef long long ll;

ll sum_tree[MAXN << 2];
ll lazy_mul[MAXN << 2];
ll lazy_add_tree[MAXN << 2];
ll m;
ll a[MAXN];

ll min_ll(ll a, ll b) {
    return a < b ? a : b;
}

void build(int node, int l, int r) {
    lazy_mul[node] = 1;
    lazy_add_tree[node] = 0;
    if (l == r) {
        sum_tree[node] = a[l] % m;
        return;
    }
    int mid = (l + r) / 2;
    build(node << 1, l, mid);
    build(node << 1 | 1, mid + 1, r);
    sum_tree[node] = (sum_tree[node << 1] + sum_tree[node << 1 | 1]) % m;
}

void push_down(int node, int l, int r) {
    int mid = (l + r) / 2;
    int left = node << 1;
    int right = node << 1 | 1;

    // Apply multiplication
    sum_tree[left] = (sum_tree[left] * lazy_mul[node] % m + (mid - l + 1) * lazy_add_tree[node] % m) % m;
    sum_tree[right] = (sum_tree[right] * lazy_mul[node] % m + (r - mid) * lazy_add_tree[node] % m) % m;

    // Update children's lazy_mul and lazy_add
    lazy_mul[left] = (lazy_mul[left] * lazy_mul[node]) % m;
    lazy_add_tree[left] = (lazy_add_tree[left] * lazy_mul[node] % m + lazy_add_tree[node]) % m;

    lazy_mul[right] = (lazy_mul[right] * lazy_mul[node]) % m;
    lazy_add_tree[right] = (lazy_add_tree[right] * lazy_mul[node] % m + lazy_add_tree[node]) % m;

    // Reset current node's lazy values
    lazy_mul[node] = 1;
    lazy_add_tree[node] = 0;
}

void range_mul(int node, int l, int r, int L, int R, ll k) {
    if (R < l || L > r) return;
    if (L <= l && r <= R) {
        sum_tree[node] = sum_tree[node] * k % m;
        lazy_mul[node] = lazy_mul[node] * k % m;
        lazy_add_tree[node] = lazy_add_tree[node] * k % m;
        return;
    }
    push_down(node, l, r);
    int mid = (l + r) / 2;
    range_mul(node << 1, l, mid, L, R, k);
    range_mul(node << 1 | 1, mid + 1, r, L, R, k);
    sum_tree[node] = (sum_tree[node << 1] + sum_tree[node << 1 | 1]) % m;
}

void range_add(int node, int l, int r, int L, int R, ll k) {
    if (R < l || L > r) return;
    if (L <= l && r <= R) {
        sum_tree[node] = (sum_tree[node] + (r - l + 1) * k % m) % m;
        lazy_add_tree[node] = (lazy_add_tree[node] + k) % m;
        return;
    }
    push_down(node, l, r);
    int mid = (l + r) / 2;
    range_add(node << 1, l, mid, L, R, k);
    range_add(node << 1 | 1, mid + 1, r, L, R, k);
    sum_tree[node] = (sum_tree[node << 1] + sum_tree[node << 1 | 1]) % m;
}

ll query_sum_func(int node, int l, int r, int L, int R) {
    if (R < l || L > r) return 0;
    if (L <= l && r <= R) {
        return sum_tree[node] % m;
    }
    push_down(node, l, r);
    int mid = (l + r) / 2;
    ll res = 0;
    res = (res + query_sum_func(node << 1, l, mid, L, R)) % m;
    res = (res + query_sum_func(node << 1 | 1, mid + 1, r, L, R)) % m;
    return res;
}

int main(){
    int n, q;
    scanf("%d %d %lld", &n, &q, &m);
    for(int i=1;i<=n;i++) {
        scanf("%lld", &a[i]);
    }
    build(1, 1, n);
    for(int i=0;i<q;i++){
        int type;
        scanf("%d", &type);
        if(type == 1){
            int x, y;
            ll k;
            scanf("%d %d %lld", &x, &y, &k);
            range_mul(1, 1, n, x, y, k % m);
        }
        else if(type == 2){
            int x, y;
            ll k;
            scanf("%d %d %lld", &x, &y, &k);
            range_add(1, 1, n, x, y, k % m);
        }
        else if(type == 3){
            int x, y;
            scanf("%d %d", &x, &y);
            ll res = query_sum_func(1, 1, n, x, y) % m;
            printf("%lld\n", res);
        }
    }
    return 0;
}