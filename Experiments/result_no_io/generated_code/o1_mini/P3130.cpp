#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

#define MAX 800005

ll sum_tree[MAX];
ll min_tree[MAX];
ll lazy[MAX];
int N, Q;
ll A_init[200005];

ll min_ll(ll a, ll b){
    return a < b ? a : b;
}

void build(int node, int l, int r){
    if(l == r){
        sum_tree[node] = A_init[l];
        min_tree[node] = A_init[l];
        return;
    }
    int mid = (l + r) / 2;
    build(node*2, l, mid);
    build(node*2+1, mid+1, r);
    sum_tree[node] = sum_tree[node*2] + sum_tree[node*2+1];
    min_tree[node] = min_ll(min_tree[node*2], min_tree[node*2+1]);
}

void pushdown(int node, int l, int r){
    if(lazy[node] != 0){
        int mid = (l + r) / 2;
        ll val = lazy[node];
        sum_tree[node*2] += val * (mid - l + 1);
        min_tree[node*2] += val;
        lazy[node*2] += val;
        sum_tree[node*2+1] += val * (r - mid);
        min_tree[node*2+1] += val;
        lazy[node*2+1] += val;
        lazy[node] = 0;
    }
}

void update_range(int node, int l, int r, int L, int R, ll val){
    if(R < l || L > r){
        return;
    }
    if(L <= l && r <= R){
        sum_tree[node] += val * (r - l + 1);
        min_tree[node] += val;
        lazy[node] += val;
        return;
    }
    pushdown(node, l, r);
    int mid = (l + r) / 2;
    update_range(node*2, l, mid, L, R, val);
    update_range(node*2+1, mid+1, r, L, R, val);
    sum_tree[node] = sum_tree[node*2] + sum_tree[node*2+1];
    min_tree[node] = min_ll(min_tree[node*2], min_tree[node*2+1]);
}

ll query_sum(int node, int l, int r, int L, int R){
    if(R < l || L > r){
        return 0;
    }
    if(L <= l && r <= R){
        return sum_tree[node];
    }
    pushdown(node, l, r);
    int mid = (l + r) / 2;
    return query_sum(node*2, l, mid, L, R) + query_sum(node*2+1, mid+1, r, L, R);
}

ll query_min(int node, int l, int r, int L, int R){
    if(R < l || L > r){
        return 1000000000;
    }
    if(L <= l && r <= R){
        return min_tree[node];
    }
    pushdown(node, l, r);
    int mid = (l + r) / 2;
    ll res1 = query_min(node*2, l, mid, L, R);
    ll res2 = query_min(node*2+1, mid+1, r, L, R);
    return min_ll(res1, res2);
}

int main(){
    scanf("%d %d", &N, &Q);
    for(int i=1;i<=N;i++) scanf("%lld", &A_init[i]);
    build(1,1,N);
    char cmd;
    int A, B;
    ll C;
    for(int i=0;i<Q;i++){
        scanf(" %c", &cmd);
        if(cmd == 'P'){
            scanf("%d %d %lld", &A, &B, &C);
            update_range(1,1,N,A,B,C);
        }
        else if(cmd == 'M'){
            scanf("%d %d", &A, &B);
            ll res = query_min(1,1,N,A,B);
            printf("%lld\n", res);
        }
        else if(cmd == 'S'){
            scanf("%d %d", &A, &B);
            ll res = query_sum(1,1,N,A,B);
            printf("%lld\n", res);
        }
    }
    return 0;
}