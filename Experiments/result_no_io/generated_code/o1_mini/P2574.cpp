#include <stdio.h>
#include <string.h>

#define MAXN 200005
int tree[4*MAXN];
int lazy_tree[4*MAXN];
char S[MAXN];

void push_down(int pos, int l, int r){
    if(lazy_tree[pos]){
        int mid = (l + r) / 2;
        // Flip left child
        tree[pos*2] = (mid - l +1) - tree[pos*2];
        // Flip right child
        tree[pos*2+1] = (r - mid) - tree[pos*2+1];
        // Mark children as lazy
        lazy_tree[pos*2] ^= 1;
        lazy_tree[pos*2+1] ^= 1;
        // Clear current node's lazy flag
        lazy_tree[pos] = 0;
    }
}

void build_tree(int pos, int l, int r){
    if(l == r){
        tree[pos] = (S[l] == '1') ? 1 : 0;
        return;
    }
    int mid = (l + r) / 2;
    build_tree(pos*2, l, mid);
    build_tree(pos*2+1, mid+1, r);
    tree[pos] = tree[pos*2] + tree[pos*2+1];
}

void update_tree(int pos, int l, int r, int ql, int qr){
    if(qr < l || ql > r){
        return;
    }
    if(ql <= l && r <= qr){
        tree[pos] = (r - l +1) - tree[pos];
        lazy_tree[pos] ^=1;
        return;
    }
    push_down(pos, l, r);
    int mid = (l + r) / 2;
    update_tree(pos*2, l, mid, ql, qr);
    update_tree(pos*2+1, mid+1, r, ql, qr);
    tree[pos] = tree[pos*2] + tree[pos*2+1];
}

int query_tree(int pos, int l, int r, int ql, int qr){
    if(qr < l || ql > r){
        return 0;
    }
    if(ql <= l && r <= qr){
        return tree[pos];
    }
    push_down(pos, l, r);
    int mid = (l + r)/2;
    int res =0;
    res += query_tree(pos*2, l, mid, ql, qr);
    res += query_tree(pos*2+1, mid+1, r, ql, qr);
    return res;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    scanf("%s", S+1); // 1-based
    build_tree(1, 1, n);
    int op, l, r;
    for(int i=0; i<m; i++){
        scanf("%d %d %d", &op, &l, &r);
        if(op == 0){
            update_tree(1, 1, n, l, r);
        }
        else{
            int res = query_tree(1,1,n,l,r);
            printf("%d\n", res);
        }
    }
    return 0;
}