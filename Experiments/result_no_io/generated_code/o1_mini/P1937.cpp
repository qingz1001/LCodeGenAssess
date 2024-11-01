#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct {
    int A;
    int B;
} Request;

typedef struct {
    int left;
    int right;
    int min;
    int lazy;
} Node;

int N, M;
int C[100005];
Request requests[100005];
Node segTree[400020];

int min_val(int a, int b) {
    return a < b ? a : b;
}

void build(int idx, int l, int r) {
    segTree[idx].left = l;
    segTree[idx].right = r;
    segTree[idx].lazy = 0;
    if (l == r) {
        segTree[idx].min = C[l];
        return;
    }
    int mid = (l + r) / 2;
    build(2*idx, l, mid);
    build(2*idx+1, mid+1, r);
    segTree[idx].min = min_val(segTree[2*idx].min, segTree[2*idx+1].min);
}

void push_down(int idx) {
    if (segTree[idx].lazy != 0) {
        segTree[2*idx].min += segTree[idx].lazy;
        segTree[2*idx+1].min += segTree[idx].lazy;
        segTree[2*idx].lazy += segTree[idx].lazy;
        segTree[2*idx+1].lazy += segTree[idx].lazy;
        segTree[idx].lazy = 0;
    }
}

int query_min(int idx, int l, int r) {
    if (segTree[idx].left > r || segTree[idx].right < l)
        return 1000000;
    if (segTree[idx].left >= l && segTree[idx].right <= r)
        return segTree[idx].min;
    push_down(idx);
    int left_min = query_min(2*idx, l, r);
    int right_min = query_min(2*idx+1, l, r);
    return min_val(left_min, right_min);
}

void update_range(int idx, int l, int r, int val) {
    if (segTree[idx].left > r || segTree[idx].right < l)
        return;
    if (segTree[idx].left >= l && segTree[idx].right <= r) {
        segTree[idx].min += val;
        segTree[idx].lazy += val;
        return;
    }
    push_down(idx);
    update_range(2*idx, l, r, val);
    update_range(2*idx+1, l, r, val);
    segTree[idx].min = min_val(segTree[2*idx].min, segTree[2*idx+1].min);
}

int cmp(const void *a, const void *b) {
    Request *ra = (Request *)a;
    Request *rb = (Request *)b;
    if (ra->B != rb->B)
        return ra->B - rb->B;
    return ra->A - rb->A;
}

int main(){
    scanf("%d %d", &N, &M);
    for(int i=1;i<=N;i++) scanf("%d", &C[i]);
    for(int i=0;i<M;i++) scanf("%d %d", &requests[i].A, &requests[i].B);
    qsort(requests, M, sizeof(Request), cmp);
    build(1, 1, N);
    int count = 0;
    for(int i=0;i<M;i++){
        int a = requests[i].A;
        int b = requests[i].B;
        if(query_min(1, a, b) >=1){
            update_range(1, a, b, -1);
            count++;
        }
    }
    printf("%d\n", count);
    return 0;
}