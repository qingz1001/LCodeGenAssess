#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

#define MAX 100005

ll sum_tree[4*MAX];
int lazy_tree[4*MAX];
int N, M;

void push_down(int node, int l, int r){
    if(lazy_tree[node]){
        int mid = (l + r) / 2;
        int left = node*2;
        int right = node*2+1;
        sum_tree[left] = (mid - l +1) - sum_tree[left];
        sum_tree[right] = (r - mid) - sum_tree[right];
        lazy_tree[left] ^= 1;
        lazy_tree[right] ^= 1;
        lazy_tree[node] = 0;
    }
}

void update_range(int node, int l, int r, int L, int R){
    if(R < l || L > r){
        return;
    }
    if(L <= l && r <= R){
        sum_tree[node] = (r - l +1) - sum_tree[node];
        lazy_tree[node] ^= 1;
        return;
    }
    push_down(node, l, r);
    int mid = (l + r) / 2;
    update_range(node*2, l, mid, L, R);
    update_range(node*2+1, mid+1, r, L, R);
    sum_tree[node] = sum_tree[node*2] + sum_tree[node*2+1];
}

ll query_range(int node, int l, int r, int L, int R){
    if(R < l || L > r){
        return 0;
    }
    if(L <= l && r <= R){
        return sum_tree[node];
    }
    push_down(node, l, r);
    int mid = (l + r) / 2;
    return query_range(node*2, l, mid, L, R) + query_range(node*2+1, mid+1, r, L, R);
}

int main(){
    scanf("%d %d", &N, &M);
    for(int i=1;i<=4*N;i++) { sum_tree[i] = 0; lazy_tree[i] = 0; }
    for(int i=0;i<M;i++){
        int cmd, S, E;
        scanf("%d %d %d", &cmd, &S, &E);
        if(cmd == 0){
            update_range(1, 1, N, S, E);
        }
        else{
            ll res = query_range(1, 1, N, S, E);
            printf("%lld\n", res);
        }
    }
    return 0;
}