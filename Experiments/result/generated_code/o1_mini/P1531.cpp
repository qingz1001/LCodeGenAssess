#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 200005

int n, m;
int scores[MAXN];
int seg[4*MAXN];

int max_int(int a, int b){
    return a > b ? a : b;
}

void build(int node, int l, int r){
    if(l == r){
        seg[node] = scores[l];
        return;
    }
    int mid = (l + r) / 2;
    build(2*node, l, mid);
    build(2*node+1, mid+1, r);
    seg[node] = max_int(seg[2*node], seg[2*node+1]);
}

int query_max(int node, int l, int r, int ql, int qr){
    if(ql > r || qr < l){
        return -2147483648;
    }
    if(ql <= l && r <= qr){
        return seg[node];
    }
    int mid = (l + r) / 2;
    int left = query_max(2*node, l, mid, ql, qr);
    int right = query_max(2*node+1, mid+1, r, ql, qr);
    return max_int(left, right);
}

void update(int node, int l, int r, int idx, int val){
    if(l == r){
        seg[node] = val;
        return;
    }
    int mid = (l + r) / 2;
    if(idx <= mid){
        update(2*node, l, mid, idx, val);
    }
    else{
        update(2*node+1, mid+1, r, idx, val);
    }
    seg[node] = max_int(seg[2*node], seg[2*node+1]);
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i=1;i<=n;i++) scanf("%d", &scores[i]);
    build(1, 1, n);
    char c;
    int a, b;
    for(int i=0;i<m;i++){
        scanf(" %c %d %d", &c, &a, &b);
        if(c == 'Q'){
            int res = query_max(1, 1, n, a, b);
            printf("%d\n", res);
        }
        else if(c == 'U'){
            if(scores[a] < b){
                scores[a] = b;
                update(1, 1, n, a, b);
            }
        }
    }
    return 0;
}