#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

ll n, p, m;
ll a[100005];

ll sum_tree[400020];
ll add_tree[400020];
ll mul_tree[400020];

void build(int node, int l, int r){
    mul_tree[node] = 1;
    add_tree[node] = 0;
    if(l == r){
        sum_tree[node] = a[l] % p;
        return;
    }
    int mid = (l + r) / 2;
    build(node*2, l, mid);
    build(node*2+1, mid+1, r);
    sum_tree[node] = (sum_tree[node*2] + sum_tree[node*2+1]) % p;
}

void push_down(int node, int l, int r){
    if(mul_tree[node] == 1 && add_tree[node] == 0) return;
    int mid = (l + r) / 2;
    int left = node*2;
    int right = node*2+1;

    // Left child
    sum_tree[left] = (sum_tree[left] * mul_tree[node] + add_tree[node] * (mid - l +1)) % p;
    mul_tree[left] = (mul_tree[left] * mul_tree[node]) % p;
    add_tree[left] = (add_tree[left] * mul_tree[node] + add_tree[node]) % p;

    // Right child
    sum_tree[right] = (sum_tree[right] * mul_tree[node] + add_tree[node] * (r - mid)) % p;
    mul_tree[right] = (mul_tree[right] * mul_tree[node]) % p;
    add_tree[right] = (add_tree[right] * mul_tree[node] + add_tree[node]) % p;

    // Reset current node
    mul_tree[node] = 1;
    add_tree[node] = 0;
}

void range_mul(int node, int l, int r, int tl, int tr, ll c){
    if(tr < l || tl > r) return;
    if(tl <= l && r <= tr){
        sum_tree[node] = (sum_tree[node] * c) % p;
        mul_tree[node] = (mul_tree[node] * c) % p;
        add_tree[node] = (add_tree[node] * c) % p;
        return;
    }
    push_down(node, l, r);
    int mid = (l + r) / 2;
    range_mul(node*2, l, mid, tl, tr, c);
    range_mul(node*2+1, mid+1, r, tl, tr, c);
    sum_tree[node] = (sum_tree[node*2] + sum_tree[node*2+1]) % p;
}

void range_add(int node, int l, int r, int tl, int tr, ll c){
    if(tr < l || tl > r) return;
    if(tl <= l && r <= tr){
        sum_tree[node] = (sum_tree[node] + c * (r - l +1)) % p;
        add_tree[node] = (add_tree[node] + c) % p;
        return;
    }
    push_down(node, l, r);
    int mid = (l + r) / 2;
    range_add(node*2, l, mid, tl, tr, c);
    range_add(node*2+1, mid+1, r, tl, tr, c);
    sum_tree[node] = (sum_tree[node*2] + sum_tree[node*2+1]) % p;
}

ll range_sum(int node, int l, int r, int tl, int tr){
    if(tr < l || tl > r) return 0;
    if(tl <= l && r <= tr){
        return sum_tree[node] % p;
    }
    push_down(node, l, r);
    int mid = (l + r) / 2;
    ll res = range_sum(node*2, l, mid, tl, tr) + range_sum(node*2+1, mid+1, r, tl, tr);
    return res % p;
}

int main(){
    scanf("%lld %lld", &n, &p);
    for(int i=1;i<=n;i++){
        scanf("%lld", &a[i]);
    }
    build(1, 1, n);
    scanf("%lld", &m);
    for(int i=0;i<m;i++){
        int type;
        scanf("%d", &type);
        if(type == 1){
            int t, g;
            ll c;
            scanf("%d %d %lld", &t, &g, &c);
            range_mul(1, 1, n, t, g, c);
        }
        else if(type == 2){
            int t, g;
            ll c;
            scanf("%d %d %lld", &t, &g, &c);
            range_add(1, 1, n, t, g, c);
        }
        else if(type == 3){
            int t, g;
            scanf("%d %d", &t, &g);
            ll res = range_sum(1, 1, n, t, g) % p;
            printf("%lld\n", res);
        }
    }
    return 0;
}