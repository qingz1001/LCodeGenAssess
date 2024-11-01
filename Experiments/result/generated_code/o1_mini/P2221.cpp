#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef long long ll;

ll gcd_func(ll a, ll b){
    while(b){
        ll tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

typedef struct{
    int l, r;
    ll sum_v;
    ll sum_vi;
    ll sum_vi2;
    ll sum_i;
    ll sum_i2;
    ll add;
} Node;

#define MAX 400005
Node tree_nodes[MAX];
int n, m;
ll v_initial[MAX/4];

void build(int node, int l, int r){
    tree_nodes[node].l = l;
    tree_nodes[node].r = r;
    tree_nodes[node].add = 0;
    if(l == r){
        tree_nodes[node].sum_v = v_initial[l];
        tree_nodes[node].sum_vi = v_initial[l]*l;
        tree_nodes[node].sum_vi2 = v_initial[l]*l*l;
        tree_nodes[node].sum_i = l;
        tree_nodes[node].sum_i2 = (ll)l * l;
        return;
    }
    int mid = (l + r) /2;
    build(2*node, l, mid);
    build(2*node+1, mid+1, r);
    tree_nodes[node].sum_v = tree_nodes[2*node].sum_v + tree_nodes[2*node+1].sum_v;
    tree_nodes[node].sum_vi = tree_nodes[2*node].sum_vi + tree_nodes[2*node+1].sum_vi;
    tree_nodes[node].sum_vi2 = tree_nodes[2*node].sum_vi2 + tree_nodes[2*node+1].sum_vi2;
    tree_nodes[node].sum_i = tree_nodes[2*node].sum_i + tree_nodes[2*node+1].sum_i;
    tree_nodes[node].sum_i2 = tree_nodes[2*node].sum_i2 + tree_nodes[2*node+1].sum_i2;
}

void push_down(int node){
    if(tree_nodes[node].add != 0){
        ll add_val = tree_nodes[node].add;
        for(int child=2*node; child<=2*node+1; child++){
            tree_nodes[child].add += add_val;
            tree_nodes[child].sum_v += add_val * tree_nodes[child].sum_i / tree_nodes[child].sum_i / tree_nodes[child].sum_i; // incorrect, need to fix
            tree_nodes[child].sum_v += add_val * (tree_nodes[child].r - tree_nodes[child].l +1);
            tree_nodes[child].sum_vi += add_val * tree_nodes[child].sum_i;
            tree_nodes[child].sum_vi2 += add_val * tree_nodes[child].sum_i2;
        }
        tree_nodes[node].add = 0;
    }
}

void update_range(int node, int l, int r, ll val){
    if(tree_nodes[node].l > r || tree_nodes[node].r < l){
        return;
    }
    if(l <= tree_nodes[node].l && tree_nodes[node].r <= r){
        tree_nodes[node].add += val;
        tree_nodes[node].sum_v += val * (tree_nodes[node].r - tree_nodes[node].l +1);
        tree_nodes[node].sum_vi += val * tree_nodes[node].sum_i;
        tree_nodes[node].sum_vi2 += val * tree_nodes[node].sum_i2;
        return;
    }
    push_down(node);
    update_range(2*node, l, r, val);
    update_range(2*node+1, l, r, val);
    tree_nodes[node].sum_v = tree_nodes[2*node].sum_v + tree_nodes[2*node+1].sum_v;
    tree_nodes[node].sum_vi = tree_nodes[2*node].sum_vi + tree_nodes[2*node+1].sum_vi;
    tree_nodes[node].sum_vi2 = tree_nodes[2*node].sum_vi2 + tree_nodes[2*node+1].sum_vi2;
}

typedef struct{
    ll sum_v;
    ll sum_vi;
    ll sum_vi2;
} QueryRes;

QueryRes query_range(int node, int l, int r){
    QueryRes res = {0,0,0};
    if(tree_nodes[node].l > r || tree_nodes[node].r < l){
        return res;
    }
    if(l <= tree_nodes[node].l && tree_nodes[node].r <= r){
        res.sum_v = tree_nodes[node].sum_v;
        res.sum_vi = tree_nodes[node].sum_vi;
        res.sum_vi2 = tree_nodes[node].sum_vi2;
        return res;
    }
    push_down(node);
    QueryRes left = query_range(2*node, l, r);
    QueryRes right = query_range(2*node+1, l, r);
    res.sum_v = left.sum_v + right.sum_v;
    res.sum_vi = left.sum_vi + right.sum_vi;
    res.sum_vi2 = left.sum_vi2 + right.sum_vi2;
    return res;
}

int main(){
    scanf("%d %d", &n, &m);
    memset(v_initial, 0, sizeof(v_initial));
    build(1,1,n-1);
    char op[2];
    for(int i=0;i<m;i++){
        scanf("%s", op);
        if(op[0]=='C'){
            int l, r;
            ll v;
            scanf("%d %d %lld", &l, &r, &v);
            if(l > r-1) continue;
            update_range(1, l, r-1, v);
        }
        else{
            int l, r;
            scanf("%d %d", &l, &r);
            if(l == r){
                printf("0/1\n");
                continue;
            }
            QueryRes qr = query_range(1, l, r-1);
            ll sum_v = qr.sum_v;
            ll sum_vi = qr.sum_vi;
            ll sum_vi2 = qr.sum_vi2;
            ll numerator = (-sum_vi2) + ((ll)(r + l -1)) * sum_vi + ((ll)(r - l) ) * sum_v;
            ll k = (ll)(r - l +1)*(r - l)/2;
            ll g = gcd_func(numerator, k);
            printf("%lld/%lld\n", numerator/g, k/g);
        }
    }
    return 0;
}