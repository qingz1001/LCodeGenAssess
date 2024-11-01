#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

ll m;
typedef struct {
    ll sum;
    ll add_lazy;
    ll mul_lazy;
} Node;

Node *tree;
ll *arr;
int n;

void build(int node, int l, int r) {
    tree[node].mul_lazy = 1;
    tree[node].add_lazy = 0;
    if (l == r) {
        tree[node].sum = arr[l] % m;
        return;
    }
    int mid = (l + r) / 2;
    build(node*2, l, mid);
    build(node*2+1, mid+1, r);
    tree[node].sum = (tree[node*2].sum + tree[node*2+1].sum) % m;
}

void push_down(int node, int l, int r) {
    int mid = (l + r) / 2;
    int left = node*2;
    int right = node*2+1;

    // Apply multiplication
    tree[left].sum = (tree[left].sum * tree[node].mul_lazy) % m;
    tree[right].sum = (tree[right].sum * tree[node].mul_lazy) % m;

    tree[left].mul_lazy = (tree[left].mul_lazy * tree[node].mul_lazy) % m;
    tree[right].mul_lazy = (tree[right].mul_lazy * tree[node].mul_lazy) % m;

    tree[left].add_lazy = (tree[left].add_lazy * tree[node].mul_lazy) % m;
    tree[right].add_lazy = (tree[right].add_lazy * tree[node].mul_lazy) % m;

    // Apply addition
    tree[left].sum = (tree[left].sum + tree[node].add_lazy * (mid - l + 1)) % m;
    tree[right].sum = (tree[right].sum + tree[node].add_lazy * (r - mid)) % m;

    tree[left].add_lazy = (tree[left].add_lazy + tree[node].add_lazy) % m;
    tree[right].add_lazy = (tree[right].add_lazy + tree[node].add_lazy) % m;

    // Reset current node's lazies
    tree[node].mul_lazy = 1;
    tree[node].add_lazy = 0;
}

void range_mul(int node, int l, int r, int ql, int qr, ll val) {
    if (ql > r || qr < l) return;
    if (ql <= l && r <= qr) {
        tree[node].sum = (tree[node].sum * val) % m;
        tree[node].mul_lazy = (tree[node].mul_lazy * val) % m;
        tree[node].add_lazy = (tree[node].add_lazy * val) % m;
        return;
    }
    push_down(node, l, r);
    int mid = (l + r) / 2;
    range_mul(node*2, l, mid, ql, qr, val);
    range_mul(node*2+1, mid+1, r, ql, qr, val);
    tree[node].sum = (tree[node*2].sum + tree[node*2+1].sum) % m;
}

void range_add(int node, int l, int r, int ql, int qr, ll val) {
    if (ql > r || qr < l) return;
    if (ql <= l && r <= qr) {
        tree[node].sum = (tree[node].sum + val * (r - l + 1)) % m;
        tree[node].add_lazy = (tree[node].add_lazy + val) % m;
        return;
    }
    push_down(node, l, r);
    int mid = (l + r) / 2;
    range_add(node*2, l, mid, ql, qr, val);
    range_add(node*2+1, mid+1, r, ql, qr, val);
    tree[node].sum = (tree[node*2].sum + tree[node*2+1].sum) % m;
}

ll range_query(int node, int l, int r, int ql, int qr) {
    if (ql > r || qr < l) return 0;
    if (ql <= l && r <= qr) {
        return tree[node].sum;
    }
    push_down(node, l, r);
    int mid = (l + r) / 2;
    ll res = range_query(node*2, l, mid, ql, qr) + range_query(node*2+1, mid+1, r, ql, qr);
    return res % m;
}

int main(){
    int q;
    scanf("%d %d %lld", &n, &q, &m);
    arr = (ll*)malloc((n+1) * sizeof(ll));
    for(int i=1;i<=n;i++) {
        scanf("%lld", &arr[i]);
    }
    // Allocate segment tree size: 4*n
    tree = (Node*)malloc((4*n+4) * sizeof(Node));
    build(1, 1, n);
    for(int i=0;i<q;i++) {
        int op;
        scanf("%d", &op);
        if(op == 1){
            int x, y;
            ll k;
            scanf("%d %d %lld", &x, &y, &k);
            range_mul(1, 1, n, x, y, k % m);
        }
        else if(op == 2){
            int x, y;
            ll k;
            scanf("%d %d %lld", &x, &y, &k);
            range_add(1, 1, n, x, y, k % m);
        }
        else if(op == 3){
            int x, y;
            scanf("%d %d", &x, &y);
            ll res = range_query(1, 1, n, x, y) % m;
            printf("%lld\n", res);
        }
    }
    free(arr);
    free(tree);
    return 0;
}