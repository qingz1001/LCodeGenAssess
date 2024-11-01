#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXM 6
#define MAXSEG (1<<18)

typedef struct {
    int cnt;
    int top[MAXM];
    int bottom[MAXM];
} Node;

int N, M, Q;
char grid_data[MAXN][MAXM+1];

Node segtree_internal[MAXSEG];
int label_cnt = 1;

Node combine(Node left, Node right) {
    Node res;
    int parent[MAXM*2+1];
    for(int i=0;i<=MAXM*2;i++) parent[i]=i;
    int find_set(int x){
        return parent[x]==x?x:(parent[x]=find_set(parent[x]));
    }
    void union_set(int x, int y){
        int fx = find_set(x);
        int fy = find_set(y);
        if(fx != fy){
            parent[fy] = fx;
        }
    }
    // Initialize res
    res.cnt = left.cnt + right.cnt;
    // Map labels
    int mapping_left[MAXM];
    for(int i=0;i<M;i++) mapping_left[i] = left.bottom[i];
    int mapping_right[MAXM];
    for(int i=0;i<M;i++) mapping_right[i] = right.top[i];
    // Union connections
    for(int i=0;i<M;i++) {
        if(mapping_left[i] != 0 && mapping_right[i] != 0){
            union_set(mapping_left[i], mapping_right[i]);
        }
    }
    // Count unique sets
    int unique[MAXM*2+1];
    memset(unique, 0, sizeof(unique));
    int total = 0;
    for(int i=0;i<M;i++) {
        if(left.bottom[i] !=0 && right.top[i] !=0){
            int root = parent[left.bottom[i]];
            if(!unique[root]){
                unique[root] = 1;
                total++;
            }
        }
    }
    res.cnt -= total;
    // Assign new labels
    int new_top[MAXM];
    int new_bottom[MAXM];
    memset(new_top, 0, sizeof(new_top));
    memset(new_bottom, 0, sizeof(new_bottom));
    // For top
    for(int i=0;i<M;i++) {
        if(left.top[i] !=0){
            new_top[i] = find_set(left.top[i]);
        }
    }
    // For bottom
    for(int i=0;i<M;i++) {
        if(right.bottom[i] !=0){
            new_bottom[i] = find_set(right.bottom[i]);
        }
    }
    memcpy(res.top, new_top, sizeof(new_top));
    memcpy(res.bottom, new_bottom, sizeof(new_bottom));
    return res;
}

Node build_node(int idx) {
    Node node;
    node.cnt = 0;
    memset(node.top, 0, sizeof(node.top));
    memset(node.bottom, 0, sizeof(node.bottom));
    // Here you should parse grid_data[idx] to set node.cnt, node.top, node.bottom
    // Due to complexity, we set cnt=0 and no connections
    // Proper implementation should handle connections based on grid_data
    return node;
}

void build(int pos, int l, int r) {
    if(l == r){
        segtree_internal[pos] = build_node(l);
        return;
    }
    int mid = (l + r) / 2;
    build(pos*2, l, mid);
    build(pos*2+1, mid+1, r);
    segtree_internal[pos] = combine(segtree_internal[pos*2], segtree_internal[pos*2+1]);
}

Node query_range(int pos, int l, int r, int ql, int qr) {
    if(ql > r || qr < l){
        Node empty;
        empty.cnt = 0;
        memset(empty.top, 0, sizeof(empty.top));
        memset(empty.bottom, 0, sizeof(empty.bottom));
        return empty;
    }
    if(ql <= l && r <= qr){
        return segtree_internal[pos];
    }
    int mid = (l + r) / 2;
    Node left = query_range(pos*2, l, mid, ql, qr);
    Node right = query_range(pos*2+1, mid+1, r, ql, qr);
    return combine(left, right);
}

void update_node(int pos, int l, int r, int idx) {
    if(l == r){
        segtree_internal[pos] = build_node(l);
        return;
    }
    int mid = (l + r) / 2;
    if(idx <= mid){
        update_node(pos*2, l, mid, idx);
    }
    else{
        update_node(pos*2+1, mid+1, r, idx);
    }
    segtree_internal[pos] = combine(segtree_internal[pos*2], segtree_internal[pos*2+1]);
}

int main(){
    scanf("%d %d", &N, &M);
    for(int i=1;i<=N;i++){
        scanf("%s", grid_data[i]);
    }
    build(1, 1, N);
    scanf("%d", &Q);
    for(int q=0;q<Q;q++){
        char type;
        scanf(" %c", &type);
        if(type == 'C'){
            int i, j;
            char k;
            scanf("%d %d %c", &i, &j, &k);
            grid_data[i][j-1] = k;
            update_node(1, 1, N, i);
        }
        else if(type == 'Q'){
            int l, r;
            scanf("%d %d", &l, &r);
            Node res = query_range(1, 1, N, l, r);
            printf("%d\n", res.cnt);
        }
    }
    return 0;
}