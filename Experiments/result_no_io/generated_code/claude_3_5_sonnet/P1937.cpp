#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXM 100005

typedef struct {
    int start, end, idx;
} Request;

int N, M;
int capacity[MAXN];
Request requests[MAXM];
int tree[MAXN * 4];
int lazy[MAXN * 4];
int result[MAXM];

int cmp(const void *a, const void *b) {
    return ((Request*)a)->end - ((Request*)b)->end;
}

void push_down(int node, int l, int r) {
    if (lazy[node]) {
        tree[node] += lazy[node];
        if (l != r) {
            lazy[node*2] += lazy[node];
            lazy[node*2+1] += lazy[node];
        }
        lazy[node] = 0;
    }
}

void update(int node, int l, int r, int ql, int qr, int val) {
    push_down(node, l, r);
    if (l > qr || r < ql) return;
    if (ql <= l && r <= qr) {
        lazy[node] += val;
        push_down(node, l, r);
        return;
    }
    int mid = (l + r) / 2;
    update(node*2, l, mid, ql, qr, val);
    update(node*2+1, mid+1, r, ql, qr, val);
    tree[node] = (tree[node*2] > tree[node*2+1]) ? tree[node*2] : tree[node*2+1];
}

int query(int node, int l, int r, int ql, int qr) {
    push_down(node, l, r);
    if (l > qr || r < ql) return 0;
    if (ql <= l && r <= qr) return tree[node];
    int mid = (l + r) / 2;
    int left = query(node*2, l, mid, ql, qr);
    int right = query(node*2+1, mid+1, r, ql, qr);
    return (left > right) ? left : right;
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &capacity[i]);
    }
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &requests[i].start, &requests[i].end);
        requests[i].idx = i;
    }
    
    qsort(requests, M, sizeof(Request), cmp);
    
    int count = 0;
    for (int i = 0; i < M; i++) {
        int max_cows = query(1, 1, N, requests[i].start, requests[i].end);
        if (max_cows < capacity[requests[i].start]) {
            update(1, 1, N, requests[i].start, requests[i].end, 1);
            result[requests[i].idx] = 1;
            count++;
        }
    }
    
    printf("%d\n", count);
    
    return 0;
}