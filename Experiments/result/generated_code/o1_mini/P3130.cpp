#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

typedef struct {
    ll sum;
    ll mn;
    ll lazy;
} Node;

int N, Q;
ll A_initial[200005];
Node tree_nodes[800020];

void build(int node, int l, int r){
    tree_nodes[node].lazy = 0;
    if(l == r){
        tree_nodes[node].sum = A_initial[l];
        tree_nodes[node].mn = A_initial[l];
        return;
    }
    int mid = (l + r) / 2;
    build(2*node, l, mid);
    build(2*node+1, mid+1, r);
    tree_nodes[node].sum = tree_nodes[2*node].sum + tree_nodes[2*node+1].sum;
    tree_nodes[node].mn = tree_nodes[2*node].mn < tree_nodes[2*node+1].mn ? tree_nodes[2*node].mn : tree_nodes[2*node+1].mn;
}

void push_down(int node, int l, int r){
    if(tree_nodes[node].lazy != 0){
        ll val = tree_nodes[node].lazy;
        int mid = (l + r) / 2;
        // Left child
        tree_nodes[2*node].sum += val * (mid - l + 1);
        tree_nodes[2*node].mn += val;
        tree_nodes[2*node].lazy += val;
        // Right child
        tree_nodes[2*node+1].sum += val * (r - mid);
        tree_nodes[2*node+1].mn += val;
        tree_nodes[2*node+1].lazy += val;
        // Clear lazy
        tree_nodes[node].lazy = 0;
    }
}

void update_range(int node, int l, int r, int ul, int ur, ll val){
    if(ul > r || ur < l) return;
    if(ul <= l && r <= ur){
        tree_nodes[node].sum += val * (r - l + 1);
        tree_nodes[node].mn += val;
        tree_nodes[node].lazy += val;
        return;
    }
    push_down(node, l, r);
    int mid = (l + r) / 2;
    update_range(2*node, l, mid, ul, ur, val);
    update_range(2*node+1, mid+1, r, ul, ur, val);
    tree_nodes[node].sum = tree_nodes[2*node].sum + tree_nodes[2*node+1].sum;
    tree_nodes[node].mn = tree_nodes[2*node].mn < tree_nodes[2*node+1].mn ? tree_nodes[2*node].mn : tree_nodes[2*node+1].mn;
}

ll query_sum(int node, int l, int r, int ql, int qr){
    if(ql > r || qr < l) return 0;
    if(ql <= l && r <= qr){
        return tree_nodes[node].sum;
    }
    push_down(node, l, r);
    int mid = (l + r) / 2;
    return query_sum(2*node, l, mid, ql, qr) + query_sum(2*node+1, mid+1, r, ql, qr);
}

ll query_min(int node, int l, int r, int ql, int qr){
    if(ql > r || qr < l) return 1000000000;
    if(ql <= l && r <= qr){
        return tree_nodes[node].mn;
    }
    push_down(node, l, r);
    int mid = (l + r) / 2;
    ll left_min = query_min(2*node, l, mid, ql, qr);
    ll right_min = query_min(2*node+1, mid+1, r, ql, qr);
    return left_min < right_min ? left_min : right_min;
}

int main(){
    scanf("%d %d", &N, &Q);
    for(int i=1;i<=N;i++) scanf("%lld", &A_initial[i]);
    build(1, 1, N);
    char cmd[2];
    for(int i=0;i<Q;i++){
        scanf("%s", cmd);
        if(cmd[0]=='M'){
            int A, B;
            scanf("%d %d", &A, &B);
            ll res = query_min(1, 1, N, A, B);
            printf("%lld\n", res);
        }
        else if(cmd[0]=='S'){
            int A, B;
            scanf("%d %d", &A, &B);
            ll res = query_sum(1, 1, N, A, B);
            printf("%lld\n", res);
        }
        else if(cmd[0]=='P'){
            int A, B;
            ll C;
            scanf("%d %d %lld", &A, &B, &C);
            update_range(1, 1, N, A, B, C);
        }
    }
    return 0;
}