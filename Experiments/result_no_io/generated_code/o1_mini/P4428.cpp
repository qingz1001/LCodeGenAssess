#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

typedef struct {
    int c0;
    int c1;
    int lazy;
} Node;

int n, m;
int bits_arr[100005];
ll prefix_parity[100005];
Node seg_tree[400020];

void build(int node, int l, int r) {
    if (l == r) {
        if (prefix_parity[l] == 0)
            seg_tree[node].c0 = 1, seg_tree[node].c1 = 0;
        else
            seg_tree[node].c0 = 0, seg_tree[node].c1 = 1;
        seg_tree[node].lazy = 0;
        return;
    }
    int mid = (l + r) / 2;
    build(node*2, l, mid);
    build(node*2+1, mid+1, r);
    seg_tree[node].c0 = seg_tree[node*2].c0 + seg_tree[node*2+1].c0;
    seg_tree[node].c1 = seg_tree[node*2].c1 + seg_tree[node*2+1].c1;
    seg_tree[node].lazy = 0;
}

void push_down(int node, int l, int r) {
    if (seg_tree[node].lazy) {
        int mid = (l + r) / 2;
        // Flip left child
        seg_tree[node*2].lazy ^= 1;
        int tmp = seg_tree[node*2].c0;
        seg_tree[node*2].c0 = seg_tree[node*2].c1;
        seg_tree[node*2].c1 = tmp;
        // Flip right child
        seg_tree[node*2+1].lazy ^=1;
        tmp = seg_tree[node*2+1].c0;
        seg_tree[node*2+1].c0 = seg_tree[node*2+1].c1;
        seg_tree[node*2+1].c1 = tmp;
        // Clear lazy
        seg_tree[node].lazy = 0;
    }
}

void update_range(int node, int l, int r, int ul, int ur) {
    if (ul > r || ur < l)
        return;
    if (ul <= l && r <= ur) {
        seg_tree[node].lazy ^=1;
        int tmp = seg_tree[node].c0;
        seg_tree[node].c0 = seg_tree[node].c1;
        seg_tree[node].c1 = tmp;
        return;
    }
    push_down(node, l, r);
    int mid = (l + r) /2;
    update_range(node*2, l, mid, ul, ur);
    update_range(node*2+1, mid+1, r, ul, ur);
    seg_tree[node].c0 = seg_tree[node*2].c0 + seg_tree[node*2+1].c0;
    seg_tree[node].c1 = seg_tree[node*2].c1 + seg_tree[node*2+1].c1;
}

void query_range(int node, int l, int r, int ql, int qr, int *cnt0, int *cnt1) {
    if (ql > r || qr < l)
        return;
    if (ql <= l && r <= qr) {
        *cnt0 += seg_tree[node].c0;
        *cnt1 += seg_tree[node].c1;
        return;
    }
    push_down(node, l, r);
    int mid = (l + r) /2;
    query_range(node*2, l, mid, ql, qr, cnt0, cnt1);
    query_range(node*2+1, mid+1, r, ql, qr, cnt0, cnt1);
}

int main(){
    scanf("%d", &n);
    for(int i=1;i<=n;i++) scanf("%d", &bits_arr[i]);
    prefix_parity[0]=0;
    for(int i=1;i<=n;i++) prefix_parity[i] = prefix_parity[i-1]^bits_arr[i];
    build(1, 0, n);
    scanf("%d", &m);
    for(int i=0;i<m;i++){
        int type;
        scanf("%d", &type);
        if(type ==1){
            int pos;
            scanf("%d", &pos);
            bits_arr[pos] ^=1;
            // Update prefix_parity from pos to n
            update_range(1, 0, n, pos, n);
        }
        else{
            int l, r;
            scanf("%d %d", &l, &r);
            int cnt0=0, cnt1=0;
            query_range(1,0,n,l-1, r, &cnt0, &cnt1);
            ll res = ((ll)cnt0 * (cnt0-1))/2 + ((ll)cnt1 * (cnt1-1))/2;
            printf("%lld\n", res);
        }
    }
    return 0;
}