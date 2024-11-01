#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    double sum;
    double sumsq;
    double lazy;
} Node;

int N, M;
double A_initial[100005];
Node tree[400020];

void build(int idx, int l, int r) {
    tree[idx].lazy = 0.0;
    if (l == r) {
        tree[idx].sum = A_initial[l];
        tree[idx].sumsq = A_initial[l] * A_initial[l];
        return;
    }
    int mid = (l + r) / 2;
    build(idx*2, l, mid);
    build(idx*2+1, mid+1, r);
    tree[idx].sum = tree[idx*2].sum + tree[idx*2+1].sum;
    tree[idx].sumsq = tree[idx*2].sumsq + tree[idx*2+1].sumsq;
}

void push_down(int idx, int l, int r) {
    if (tree[idx].lazy != 0.0) {
        double k = tree[idx].lazy;
        int mid = (l + r) / 2;
        int left = idx*2;
        int right = idx*2+1;
        int len1 = mid - l + 1;
        int len2 = r - mid;
        // Update left child
        tree[left].sumsq += 2.0 * k * tree[left].sum + k * k * len1;
        tree[left].sum += k * len1;
        tree[left].lazy += k;
        // Update right child
        tree[right].sumsq += 2.0 * k * tree[right].sum + k * k * len2;
        tree[right].sum += k * len2;
        tree[right].lazy += k;
        // Clear lazy
        tree[idx].lazy = 0.0;
    }
}

void update_range(int idx, int l, int r, int ul, int ur, double k) {
    if (ul > r || ur < l) return;
    if (ul <= l && r <= ur) {
        int len = r - l + 1;
        tree[idx].sumsq += 2.0 * k * tree[idx].sum + k * k * len;
        tree[idx].sum += k * len;
        tree[idx].lazy += k;
        return;
    }
    push_down(idx, l, r);
    int mid = (l + r) / 2;
    update_range(idx*2, l, mid, ul, ur, k);
    update_range(idx*2+1, mid+1, r, ul, ur, k);
    tree[idx].sum = tree[idx*2].sum + tree[idx*2+1].sum;
    tree[idx].sumsq = tree[idx*2].sumsq + tree[idx*2+1].sumsq;
}

void query_range(int idx, int l, int r, int ql, int qr, double* s, double* ss) {
    if (ql > r || qr < l) return;
    if (ql <= l && r <= qr) {
        *s += tree[idx].sum;
        *ss += tree[idx].sumsq;
        return;
    }
    push_down(idx, l, r);
    int mid = (l + r) / 2;
    query_range(idx*2, l, mid, ql, qr, s, ss);
    query_range(idx*2+1, mid+1, r, ql, qr, s, ss);
}

int main(){
    scanf("%d %d", &N, &M);
    for(int i=1;i<=N;i++) scanf("%lf", &A_initial[i]);
    build(1,1,N);
    for(int i=0;i<M;i++){
        int op;
        scanf("%d", &op);
        if(op == 1){
            int x, y;
            double k;
            scanf("%d %d %lf", &x, &y, &k);
            update_range(1,1,N,x,y,k);
        }
        else{
            int x, y;
            scanf("%d %d", &x, &y);
            double s=0.0, ss=0.0;
            query_range(1,1,N,x,y,&s,&ss);
            int cnt = y - x +1;
            if(op ==2){
                double avg = s / cnt;
                printf("%.4lf\n", avg);
            }
            else{
                double avg = s / cnt;
                double var = (ss / cnt) - (avg * avg);
                printf("%.4lf\n", var);
            }
        }
    }
    return 0;
}