#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

typedef struct {
    int left;
    int right;
    int count;
    int lazy;
} Node;

Node tree[800005];
int n, m;
char S[200005];

void build(int idx, int l, int r){
    tree[idx].left = l;
    tree[idx].right = r;
    tree[idx].lazy = 0;
    if(l == r){
        tree[idx].count = S[l-1] - '0';
        return;
    }
    int mid = (l + r) / 2;
    build(2*idx, l, mid);
    build(2*idx+1, mid+1, r);
    tree[idx].count = tree[2*idx].count + tree[2*idx+1].count;
}

void push_down(int idx){
    if(tree[idx].lazy){
        int left = 2*idx;
        int right = 2*idx+1;
        // Flip left child
        tree[left].count = tree[left].right - tree[left].left + 1 - tree[left].count;
        tree[left].lazy ^= 1;
        // Flip right child
        tree[right].count = tree[right].right - tree[right].left + 1 - tree[right].count;
        tree[right].lazy ^= 1;
        // Clear current node's lazy flag
        tree[idx].lazy = 0;
    }
}

void update(int idx, int l, int r){
    if(tree[idx].left > r || tree[idx].right < l){
        return;
    }
    if(tree[idx].left >= l && tree[idx].right <= r){
        tree[idx].count = tree[idx].right - tree[idx].left + 1 - tree[idx].count;
        tree[idx].lazy ^= 1;
        return;
    }
    push_down(idx);
    update(2*idx, l, r);
    update(2*idx+1, l, r);
    tree[idx].count = tree[2*idx].count + tree[2*idx+1].count;
}

int query(int idx, int l, int r){
    if(tree[idx].left > r || tree[idx].right < l){
        return 0;
    }
    if(tree[idx].left >= l && tree[idx].right <= r){
        return tree[idx].count;
    }
    push_down(idx);
    return query(2*idx, l, r) + query(2*idx+1, l, r);
}

int main(){
    scanf("%d %d", &n, &m);
    scanf("%s", S);
    build(1, 1, n);
    int op, l, r;
    for(int i = 0; i < m; i++){
        scanf("%d %d %d", &op, &l, &r);
        if(op == 0){
            update(1, l, r);
        }
        else{
            int res = query(1, l, r);
            printf("%d\n", res);
        }
    }
    return 0;
}