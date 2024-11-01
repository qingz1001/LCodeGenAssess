#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int S;
    int E;
    int M;
} Request;

int compare(const void *a, const void *b){
    Request *ra = (Request*)a;
    Request *rb = (Request*)b;
    if (ra->E != rb->E)
        return ra->E - rb->E;
    return ra->S - rb->S;
}

int N, C;
int tree_max_val[80005];
int tree_lazy_val[80005];

void push_down(int node, int l, int r){
    if (tree_lazy_val[node] != 0){
        int mid = (l + r) / 2;
        int left = node * 2;
        int right = node * 2 + 1;
        tree_max_val[left] += tree_lazy_val[node];
        tree_max_val[right] += tree_lazy_val[node];
        tree_lazy_val[left] += tree_lazy_val[node];
        tree_lazy_val[right] += tree_lazy_val[node];
        tree_lazy_val[node] = 0;
    }
}

int query_max(int node, int l, int r, int ql, int qr){
    if (ql > r || qr < l)
        return 0;
    if (ql <= l && r <= qr)
        return tree_max_val[node];
    push_down(node, l, r);
    int mid = (l + r) / 2;
    int left_max = query_max(node*2, l, mid, ql, qr);
    int right_max = query_max(node*2+1, mid+1, r, ql, qr);
    return left_max > right_max ? left_max : right_max;
}

void update_range(int node, int l, int r, int ql, int qr, int delta){
    if (ql > r || qr < l)
        return;
    if (ql <= l && r <= qr){
        tree_max_val[node] += delta;
        tree_lazy_val[node] += delta;
        return;
    }
    push_down(node, l, r);
    int mid = (l + r) / 2;
    update_range(node*2, l, mid, ql, qr, delta);
    update_range(node*2+1, mid+1, r, ql, qr, delta);
    tree_max_val[node] = tree_max_val[node*2] > tree_max_val[node*2+1] ? tree_max_val[node*2] : tree_max_val[node*2+1];
}

int main(){
    int K;
    scanf("%d %d %d", &K, &N, &C);
    Request *req = (Request*)malloc(sizeof(Request)*K);
    for(int i=0;i<K;i++){
        scanf("%d %d %d", &req[i].S, &req[i].E, &req[i].M);
    }
    qsort(req, K, sizeof(Request), compare);
    long long total = 0;
    for(int i=0;i<K;i++){
        int S = req[i].S;
        int E = req[i].E -1;
        if(S > E){
            continue;
        }
        int current_max = query_max(1, 1, N, S, E);
        if(current_max >= C){
            continue;
        }
        int delta = C - current_max;
        if(delta > req[i].M){
            delta = req[i].M;
        }
        if(delta >0){
            update_range(1, 1, N, S, E, delta);
            total += delta;
        }
    }
    printf("%lld\n", total);
    free(req);
    return 0;
}