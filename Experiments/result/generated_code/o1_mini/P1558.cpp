#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

typedef struct {
    int left, right;
    unsigned int mask;
    int lazy;
} Node;

int L, T, O;
Node *tree;
unsigned int init_mask;

void build(int node, int l, int r){
    tree[node].left = l;
    tree[node].right = r;
    tree[node].lazy = -1;
    if(l == r){
        tree[node].mask = init_mask;
        return;
    }
    int mid = (l + r) / 2;
    build(2*node, l, mid);
    build(2*node+1, mid+1, r);
    tree[node].mask = tree[2*node].mask | tree[2*node+1].mask;
}

void push_down(int node){
    if(tree[node].lazy != -1){
        tree[2*node].mask = 1U << (tree[node].lazy -1);
        tree[2*node+1].mask = 1U << (tree[node].lazy -1);
        tree[2*node].lazy = tree[node].lazy;
        tree[2*node+1].lazy = tree[node].lazy;
        tree[node].lazy = -1;
    }
}

void update(int node, int l, int r, int color){
    if(tree[node].left > r || tree[node].right < l){
        return;
    }
    if(tree[node].left >= l && tree[node].right <= r){
        tree[node].mask = 1U << (color -1);
        tree[node].lazy = color;
        return;
    }
    push_down(node);
    update(2*node, l, r, color);
    update(2*node+1, l, r, color);
    tree[node].mask = tree[2*node].mask | tree[2*node+1].mask;
}

unsigned int query_mask = 0;

void query(int node, int l, int r){
    if(tree[node].left > r || tree[node].right < l){
        return;
    }
    if(tree[node].left >= l && tree[node].right <= r){
        query_mask |= tree[node].mask;
        return;
    }
    push_down(node);
    query(2*node, l, r);
    query(2*node+1, l, r);
}

int main(){
    scanf("%d %d %d", &L, &T, &O);
    tree = (Node*)malloc(sizeof(Node) * (4*L + 4));
    init_mask = 1U << 0;
    build(1, 1, L);
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
            update(1, A, B, C);
        }
        else if(op[0] == 'P'){
            scanf("%d %d", &A, &B);
            if(A > B){
                int tmp = A;
                A = B;
                B = tmp;
            }
            query_mask = 0;
            query(1, A, B);
            int cnt = 0;
            unsigned int mask = query_mask;
            while(mask){
                cnt += mask & 1;
                mask >>=1;
            }
            printf("%d\n", cnt);
        }
    }
    free(tree);
    return 0;
}