#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAXN 200005

long long tree[4 * MAXN];

void update_tree(int node, int l, int r, int pos, long long val) {
    if (l == r) {
        tree[node] = val;
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid)
        update_tree(2 * node, l, mid, pos, val);
    else
        update_tree(2 * node + 1, mid + 1, r, pos, val);
    if (tree[2 * node] > tree[2 * node + 1])
        tree[node] = tree[2 * node];
    else
        tree[node] = tree[2 * node + 1];
}

long long query_max(int node, int l, int r, int ql, int qr) {
    if (ql > r || qr < l)
        return LLONG_MIN;
    if (ql <= l && r <= qr)
        return tree[node];
    int mid = (l + r) / 2;
    long long left = query_max(2 * node, l, mid, ql, qr);
    long long right = query_max(2 * node + 1, mid + 1, r, ql, qr);
    return left > right ? left : right;
}

int main(){
    int M;
    long long D;
    scanf("%d %lld", &M, &D);
    char op[2];
    long long param;
    int N = 0;
    long long last_t = 0;
    for(int i = 0; i < M; i++){
        scanf("%s", op);
        if(op[0] == 'A'){
            scanf("%lld", &param);
            long long tmp = param + last_t;
            long long v = tmp % D;
            if(v < 0) v += D;
            N += 1;
            update_tree(1, 1, MAXN, N, v);
        }
        else if(op[0] == 'Q'){
            int L;
            scanf("%d", &L);
            int ql = N - L + 1;
            int qr = N;
            long long res = query_max(1, 1, MAXN, ql, qr);
            last_t = res;
            printf("%lld\n", res);
        }
    }
    return 0;
}