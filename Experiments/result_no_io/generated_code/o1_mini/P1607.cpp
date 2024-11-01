#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int S;
    int E;
    int M;
} Group;

int compare(const void* a, const void* b) {
    Group* g1 = (Group*)a;
    Group* g2 = (Group*)b;
    if (g1->E != g2->E)
        return g1->E - g2->E;
    return g1->S - g2->S;
}

typedef struct {
    int max_val;
    int lazy;
} Node;

Node tree_nodes[80005];
int N_global;

void push_down(int node, int l, int r) {
    if (tree_nodes[node].lazy != 0) {
        int mid = (l + r) / 2;
        int left = node * 2;
        int right = node * 2 + 1;
        tree_nodes[left].max_val += tree_nodes[node].lazy;
        tree_nodes[right].max_val += tree_nodes[node].lazy;
        tree_nodes[left].lazy += tree_nodes[node].lazy;
        tree_nodes[right].lazy += tree_nodes[node].lazy;
        tree_nodes[node].lazy = 0;
    }
}

int query_max(int node, int l, int r, int ql, int qr) {
    if (ql > r || qr < l) return 0;
    if (ql <= l && r <= qr) return tree_nodes[node].max_val;
    push_down(node, l, r);
    int mid = (l + r) / 2;
    int left_max = query_max(node*2, l, mid, ql, qr);
    int right_max = query_max(node*2+1, mid+1, r, ql, qr);
    return left_max > right_max ? left_max : right_max;
}

void update_range(int node, int l, int r, int ql, int qr, int val) {
    if (ql > r || qr < l) return;
    if (ql <= l && r <= qr) {
        tree_nodes[node].max_val += val;
        tree_nodes[node].lazy += val;
        return;
    }
    push_down(node, l, r);
    int mid = (l + r) / 2;
    update_range(node*2, l, mid, ql, qr, val);
    update_range(node*2+1, mid+1, r, ql, qr, val);
    tree_nodes[node].max_val = tree_nodes[node*2].max_val > tree_nodes[node*2+1].max_val ? tree_nodes[node*2].max_val : tree_nodes[node*2+1].max_val;
}

int main(){
    int K, N, C;
    scanf("%d %d %d", &K, &N, &C);
    Group* groups = (Group*)malloc(sizeof(Group)*K);
    for(int i=0;i<K;i++){
        scanf("%d %d %d", &groups[i].S, &groups[i].E, &groups[i].M);
    }
    qsort(groups, K, sizeof(Group), compare);
    N_global = N-1;
    long long total = 0;
    for(int i=0;i<K;i++){
        int S = groups[i].S;
        int E = groups[i].E -1;
        if(S > E) continue;
        int current_max = query_max(1, 1, N_global, S, E);
        int available = C - current_max;
        if(available <=0) continue;
        int assign = groups[i].M < available ? groups[i].M : available;
        if(assign >0){
            total += assign;
            update_range(1, 1, N_global, S, E, assign);
        }
    }
    printf("%lld\n", total);
    free(groups);
    return 0;
}