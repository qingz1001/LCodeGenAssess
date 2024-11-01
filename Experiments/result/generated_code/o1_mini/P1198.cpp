#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 200005

long long A[MAXN];
long long tree[4 * MAXN];
int N = 0;
long long D, t = 0;

// Build function is not needed since we are updating incrementally

long long max_val(long long a, long long b){
    return a > b ? a : b;
}

void update_tree(int node, int l, int r, int pos, long long val){
    if(l == r){
        tree[node] = val;
        return;
    }
    int mid = (l + r) / 2;
    if(pos <= mid){
        update_tree(2*node, l, mid, pos, val);
    }
    else{
        update_tree(2*node+1, mid+1, r, pos, val);
    }
    tree[node] = max_val(tree[2*node], tree[2*node+1]);
}

long long query_tree(int node, int l, int r, int ql, int qr){
    if(ql > r || qr < l) return -9223372036854775807LL;
    if(ql <= l && r <= qr){
        return tree[node];
    }
    int mid = (l + r) / 2;
    long long left = query_tree(2*node, l, mid, ql, qr);
    long long right = query_tree(2*node+1, mid+1, r, ql, qr);
    return max_val(left, right);
}

int main(){
    int M;
    scanf("%d %lld", &M, &D);
    char op[2];
    long long num;
    while(M--){
        scanf("%s", op);
        if(op[0] == 'A'){
            scanf("%lld", &num);
            long long val = (num + t) % D;
            A[++N] = val;
            update_tree(1, 1, MAXN, N, val);
        }
        else if(op[0] == 'Q'){
            int L;
            scanf("%d", &L);
            long long res = query_tree(1, 1, MAXN, N - L + 1, N);
            printf("%lld\n", res);
            t = res;
        }
    }
    return 0;
}