#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int A;
    int B;
} Request;

typedef struct {
    int min;
    int lazy;
} Node;

int N, M;
int C_limit[100005];
Request requests[100005];
Node tree_nodes[400020];

int min_int(int a, int b){
    return a < b ? a : b;
}

void build_tree(int id, int l, int r){
    if(l == r){
        tree_nodes[id].min = C_limit[l];
        tree_nodes[id].lazy = 0;
        return;
    }
    int mid = (l + r) / 2;
    build_tree(id*2, l, mid);
    build_tree(id*2+1, mid+1, r);
    tree_nodes[id].min = min_int(tree_nodes[id*2].min, tree_nodes[id*2+1].min);
    tree_nodes[id].lazy = 0;
}

void push_down(int id){
    if(tree_nodes[id].lazy != 0){
        tree_nodes[id*2].min += tree_nodes[id].lazy;
        tree_nodes[id*2+1].min += tree_nodes[id].lazy;
        tree_nodes[id*2].lazy += tree_nodes[id].lazy;
        tree_nodes[id*2+1].lazy += tree_nodes[id].lazy;
        tree_nodes[id].lazy = 0;
    }
}

int query_min(int id, int l, int r, int ql, int qr){
    if(ql > r || qr < l){
        return 1000000000;
    }
    if(ql <= l && r <= qr){
        return tree_nodes[id].min;
    }
    push_down(id);
    int mid = (l + r) / 2;
    int left_min = query_min(id*2, l, mid, ql, qr);
    int right_min = query_min(id*2+1, mid+1, r, ql, qr);
    return min_int(left_min, right_min);
}

void range_update(int id, int l, int r, int ql, int qr, int delta){
    if(ql > r || qr < l){
        return;
    }
    if(ql <= l && r <= qr){
        tree_nodes[id].min += delta;
        tree_nodes[id].lazy += delta;
        return;
    }
    push_down(id);
    int mid = (l + r) / 2;
    range_update(id*2, l, mid, ql, qr, delta);
    range_update(id*2+1, mid+1, r, ql, qr, delta);
    tree_nodes[id].min = min_int(tree_nodes[id*2].min, tree_nodes[id*2+1].min);
}

int cmp_requests(const void* a, const void* b){
    Request* ra = (Request*)a;
    Request* rb = (Request*)b;
    if(ra->B != rb->B){
        return ra->B - rb->B;
    }
    return ra->A - rb->A;
}

int main(){
    scanf("%d %d", &N, &M);
    for(int i=1; i<=N; i++){
        scanf("%d", &C_limit[i]);
    }
    for(int i=0; i<M; i++){
        scanf("%d %d", &requests[i].A, &requests[i].B);
    }
    qsort(requests, M, sizeof(Request), cmp_requests);
    build_tree(1, 1, N);
    int count = 0;
    for(int i=0; i<M; i++){
        int A = requests[i].A;
        int B = requests[i].B;
        int current_min = query_min(1, 1, N, A, B);
        if(current_min >=1 ){
            range_update(1, 1, N, A, B, -1);
            count++;
        }
    }
    printf("%d\n", count);
    return 0;
}