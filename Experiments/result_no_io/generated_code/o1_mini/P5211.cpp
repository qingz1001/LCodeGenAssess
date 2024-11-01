#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

const int MAX = 200005;
const ll MOD = 1000000007;
const ll P = 911382629;

// Power arrays
ll power_p[MAX];

// Segment Tree
typedef struct {
    ll hash;
    ll lazy;
} Node;

Node tree_nodes[4 * MAX];
int n;

// Initialize power_p
void init_power() {
    power_p[0] = 1;
    for(int i = 1; i < MAX; i++) {
        power_p[i] = (power_p[i-1] * P) % MOD;
    }
}

// Combine function
ll combine(ll a, ll b, int len_b) {
    return (a * power_p[len_b] + b) % MOD;
}

// Build segment tree
ll s_arr[MAX];
void build(int node, int l, int r) {
    if(l == r){
        tree_nodes[node].hash = (s_arr[l] % MOD + MOD) % MOD;
        tree_nodes[node].lazy = 0;
        return;
    }
    int mid = (l + r) / 2;
    build(node*2, l, mid);
    build(node*2+1, mid+1, r);
    int len_right = r - mid;
    tree_nodes[node].hash = (combine(tree_nodes[node*2].hash, tree_nodes[node*2+1].hash, len_right)) % MOD;
    tree_nodes[node].lazy = 0;
}

// Push down lazy
void push_down(int node, int l, int r) {
    if(tree_nodes[node].lazy != 0){
        int mid = (l + r) / 2;
        int len_right = r - mid;
        // Left child
        tree_nodes[node*2].hash = (tree_nodes[node*2].hash + (tree_nodes[node].lazy * power_p[r - mid]) % MOD * ((mid - l +1)) ) % MOD;
        tree_nodes[node*2].lazy = (tree_nodes[node*2].lazy + tree_nodes[node].lazy) % MOD;
        // Right child
        tree_nodes[node*2+1].hash = (tree_nodes[node*2+1].hash + (tree_nodes[node].lazy * power_p[r - mid - (r - mid)] ) % MOD * ((r - mid)) ) % MOD;
        tree_nodes[node*2+1].lazy = (tree_nodes[node*2+1].lazy + tree_nodes[node].lazy) % MOD;
        tree_nodes[node].lazy = 0;
    }
}

// Update range add
void update_range(int node, int l, int r, int ul, int ur, ll val) {
    if(ur < l || ul > r) return;
    if(ul <= l && r <= ur){
        tree_nodes[node].hash = (tree_nodes[node].hash + (val * power_p[r - l]) % MOD * (r - l +1) ) % MOD;
        tree_nodes[node].lazy = (tree_nodes[node].lazy + val) % MOD;
        return;
    }
    push_down(node, l, r);
    int mid = (l + r) / 2;
    update_range(node*2, l, mid, ul, ur, val);
    update_range(node*2+1, mid+1, r, ul, ur, val);
    int len_right = r - mid;
    tree_nodes[node].hash = (combine(tree_nodes[node*2].hash, tree_nodes[node*2+1].hash, len_right)) % MOD;
}

// Get hash
ll get_hash_range(int node, int l, int r, int ql, int qr) {
    if(qr < l || ql > r) return 0;
    if(ql <= l && r <= qr){
        return (tree_nodes[node].hash * power_p[MAX - r]) % MOD;
    }
    push_down(node, l, r);
    int mid = (l + r) / 2;
    ll res = (get_hash_range(node*2, l, mid, ql, qr) + get_hash_range(node*2+1, mid+1, r, ql, qr)) % MOD;
    return res;
}

// Get single value (not used)
ll get_single(int node, int l, int r, int pos) {
    if(l == r){
        return (tree_nodes[node].hash) % MOD;
    }
    push_down(node, l, r);
    int mid = (l + r) / 2;
    if(pos <= mid) return get_single(node*2, l, mid, pos);
    else return get_single(node*2+1, mid+1, r, pos);
}

// Compare two suffixes
int compare_suffix(int a, int b, int r_bound) {
    int low = 0, high = r_bound - (a > b ? a : b) +1;
    while(low < high){
        int mid = low + (high - low)/2;
        ll hash_a = get_hash_range(1, 1, n, a, a+mid-1);
        ll hash_b = get_hash_range(1, 1, n, b, b+mid-1);
        if(hash_a == hash_b){
            low = mid +1;
        }
        else{
            high = mid;
        }
    }
    if(a + low -1 > r_bound && b + low -1 > r_bound) return 0;
    if(a + low -1 > r_bound) return 1;
    if(b + low -1 > r_bound) return -1;
    ll val_a = get_single(1, 1, n, a + low);
    ll val_b = get_single(1, 1, n, b + low);
    if(val_a < val_b) return -1;
    else if(val_a > val_b) return 1;
    return 0;
}

int main(){
    init_power();
    int q;
    scanf("%d %d", &n, &q);
    for(int i=1;i<=n;i++) scanf("%lld", &s_arr[i]);
    build(1, 1, n);
    for(int i=0;i<q;i++){
        int type;
        scanf("%d", &type);
        if(type ==1){
            int l, r;
            ll d;
            scanf("%d %d %lld", &l, &r, &d);
            update_range(1, 1, n, l, r, d);
        }
        else{
            int l, r;
            scanf("%d %d", &l, &r);
            int res = l;
            for(int p = l+1; p <= r; p++){
                int cmp = compare_suffix(p, res, r);
                if(cmp == -1){
                    res = p;
                }
            }
            printf("%d\n", res);
        }
    }
    return 0;
}