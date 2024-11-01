#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double sum;
    double sum_sq;
    double lazy;
} Node;

#define MAXN 100005
Node tree_seg[400020];
double A[MAXN];
int N, M;

// Build the segment tree
void build(int node, int l, int r) {
    if (l == r) {
        tree_seg[node].sum = A[l];
        tree_seg[node].sum_sq = A[l] * A[l];
        tree_seg[node].lazy = 0.0;
        return;
    }
    int mid = (l + r) / 2;
    build(2*node, l, mid);
    build(2*node+1, mid+1, r);
    tree_seg[node].sum = tree_seg[2*node].sum + tree_seg[2*node+1].sum;
    tree_seg[node].sum_sq = tree_seg[2*node].sum_sq + tree_seg[2*node+1].sum_sq;
    tree_seg[node].lazy = 0.0;
}

// Push down the lazy updates
void push_down(int node, int l, int r) {
    if (tree_seg[node].lazy != 0.0) {
        double k = tree_seg[node].lazy;
        int mid = (l + r) / 2;
        int left = 2*node;
        int right = 2*node+1;
        int len_left = mid - l + 1;
        int len_right = r - mid;

        // Update left child
        double sum_prev_left = tree_seg[left].sum;
        tree_seg[left].sum += k * len_left;
        tree_seg[left].sum_sq += 2.0 * k * sum_prev_left + k * k * len_left;
        tree_seg[left].lazy += k;

        // Update right child
        double sum_prev_right = tree_seg[right].sum;
        tree_seg[right].sum += k * len_right;
        tree_seg[right].sum_sq += 2.0 * k * sum_prev_right + k * k * len_right;
        tree_seg[right].lazy += k;

        // Clear the lazy value
        tree_seg[node].lazy = 0.0;
    }
}

// Update range [ul, ur] by adding val
void update_range(int node, int l, int r, int ul, int ur, double val) {
    if (ul > r || ur < l)
        return;
    if (ul <= l && r <= ur) {
        double len = r - l + 1;
        tree_seg[node].sum_sq += 2.0 * val * tree_seg[node].sum + val * val * len;
        tree_seg[node].sum += val * len;
        tree_seg[node].lazy += val;
        return;
    }
    push_down(node, l, r);
    int mid = (l + r) / 2;
    update_range(2*node, l, mid, ul, ur, val);
    update_range(2*node+1, mid+1, r, ul, ur, val);
    tree_seg[node].sum = tree_seg[2*node].sum + tree_seg[2*node+1].sum;
    tree_seg[node].sum_sq = tree_seg[2*node].sum_sq + tree_seg[2*node+1].sum_sq;
}

// Query sum and sum_sq in range [ql, qr]
void query_range(int node, int l, int r, int ql, int qr, double *res_sum, double *res_sum_sq) {
    if (ql > r || qr < l)
        return;
    if (ql <= l && r <= qr) {
        *res_sum += tree_seg[node].sum;
        *res_sum_sq += tree_seg[node].sum_sq;
        return;
    }
    push_down(node, l, r);
    int mid = (l + r) / 2;
    query_range(2*node, l, mid, ql, qr, res_sum, res_sum_sq);
    query_range(2*node+1, mid+1, r, ql, qr, res_sum, res_sum_sq);
}

int main(){
    scanf("%d %d", &N, &M);
    for(int i=1;i<=N;i++) {
        scanf("%lf", &A[i]);
    }
    build(1,1,N);
    for(int i=0;i<M;i++){
        int type;
        scanf("%d", &type);
        if(type == 1){
            int x, y;
            double k;
            scanf("%d %d %lf", &x, &y, &k);
            update_range(1,1,N,x,y,k);
        }
        else if(type == 2){
            int x, y;
            scanf("%d %d", &x, &y);
            double s = 0.0, s_sq = 0.0;
            query_range(1,1,N,x,y, &s, &s_sq);
            int cnt = y - x +1;
            double avg = s / cnt;
            printf("%.4lf\n", avg);
        }
        else if(type == 3){
            int x, y;
            scanf("%d %d", &x, &y);
            double s = 0.0, s_sq = 0.0;
            query_range(1,1,N,x,y, &s, &s_sq);
            int cnt = y - x +1;
            double avg = s / cnt;
            double variance = s_sq / cnt - avg * avg;
            printf("%.4lf\n", variance);
        }
    }
    return 0;
}