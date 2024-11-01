#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct {
    int sum;
    int lazy;
} Node;

int N, M;
Node tree[400005];

void build(int node, int l, int r){
    tree[node].sum = 0;
    tree[node].lazy = 0;
    if(l == r){
        return;
    }
    int mid = (l + r) / 2;
    build(2*node, l, mid);
    build(2*node+1, mid+1, r);
}

void push_down(int node, int l, int r){
    if(tree[node].lazy){
        int mid = (l + r) / 2;
        int left = 2*node;
        int right = 2*node+1;

        tree[left].sum = (mid - l +1) - tree[left].sum;
        tree[right].sum = (r - mid) - tree[right].sum;

        tree[left].lazy ^= 1;
        tree[right].lazy ^= 1;

        tree[node].lazy = 0;
    }
}

void update_range(int node, int l, int r, int ul, int ur){
    if(ul > r || ur < l){
        return;
    }
    if(ul <= l && r <= ur){
        tree[node].sum = (r - l +1) - tree[node].sum;
        tree[node].lazy ^=1;
        return;
    }
    push_down(node, l, r);
    int mid = (l + r) / 2;
    update_range(2*node, l, mid, ul, ur);
    update_range(2*node+1, mid+1, r, ul, ur);
    tree[node].sum = tree[2*node].sum + tree[2*node+1].sum;
}

int query_range(int node, int l, int r, int ql, int qr){
    if(ql > r || qr < l){
        return 0;
    }
    if(ql <= l && r <= qr){
        return tree[node].sum;
    }
    push_down(node, l, r);
    int mid = (l + r) / 2;
    return query_range(2*node, l, mid, ql, qr) + query_range(2*node+1, mid+1, r, ql, qr);
}

int main(){
    scanf("%d %d", &N, &M);
    build(1, 1, N);
    for(int i=0;i<M;i++){
        int cmd, S, E;
        scanf("%d %d %d", &cmd, &S, &E);
        if(cmd == 0){
            update_range(1, 1, N, S, E);
        }
        else{
            int res = query_range(1, 1, N, S, E);
            printf("%d\n", res);
        }
    }
    return 0;
}