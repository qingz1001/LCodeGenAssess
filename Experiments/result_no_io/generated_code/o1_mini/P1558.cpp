#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

#define MAX 400005

int L, T, O;
unsigned int tree[MAX];
unsigned int lazy_tree[MAX];
int color_mask(int C) {
    return 1U << (C - 1);
}

void build(int l, int r, int pos){
    if(l == r){
        tree[pos] = color_mask(1);
        lazy_tree[pos] = 0;
        return;
    }
    int mid = (l + r) /2;
    build(l, mid, pos*2);
    build(mid+1, r, pos*2+1);
    tree[pos] = tree[pos*2] | tree[pos*2+1];
    lazy_tree[pos] = 0;
}

void pushdown(int pos, int l, int r){
    if(lazy_tree[pos]){
        int mid = (l + r)/2;
        tree[pos*2] = lazy_tree[pos];
        tree[pos*2+1] = lazy_tree[pos];
        lazy_tree[pos*2] = lazy_tree[pos];
        lazy_tree[pos*2+1] = lazy_tree[pos];
        lazy_tree[pos] = 0;
    }
}

void update_range(int A, int B, int C, int l, int r, int pos){
    if(B < l || A > r){
        return;
    }
    if(A <= l && r <= B){
        tree[pos] = color_mask(C);
        lazy_tree[pos] = color_mask(C);
        return;
    }
    pushdown(pos, l, r);
    int mid = (l + r)/2;
    update_range(A, B, C, l, mid, pos*2);
    update_range(A, B, C, mid+1, r, pos*2+1);
    tree[pos] = tree[pos*2] | tree[pos*2+1];
}

unsigned int query_range(int A, int B, int l, int r, int pos){
    if(B < l || A > r){
        return 0;
    }
    if(A <= l && r <= B){
        return tree[pos];
    }
    pushdown(pos, l, r);
    int mid = (l + r)/2;
    return query_range(A, B, l, mid, pos*2) | query_range(A, B, mid+1, r, pos*2+1);
}

int main(){
    scanf("%d %d %d", &L, &T, &O);
    build(1, L,1);
    char op[2];
    int A, B, C;
    for(int i=0;i<O;i++){
        scanf("%s", op);
        if(op[0] == 'C'){
            scanf("%d %d %d", &A, &B, &C);
            if(A > B){
                int tmp = A;
                A = B;
                B = tmp;
            }
            update_range(A, B, C, 1, L,1);
        }
        else{
            scanf("%d %d", &A, &B);
            if(A > B){
                int tmp = A;
                A = B;
                B = tmp;
            }
            unsigned int res = query_range(A, B,1, L,1);
            int cnt = __builtin_popcount(res);
            printf("%d\n", cnt);
        }
    }
    return 0;
}