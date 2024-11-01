#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 200005

typedef struct Edge {
    int type; // 1: produce, 2: overcome
    int u, v;
} Edge;

typedef struct Operation {
    int parent;
    int type;
    Edge edge;
} Operation;

typedef struct Node {
    int idx;
    struct Node* next;
} Node;

typedef struct {
    int parent[MAXN];
    int rank_[MAXN];
    int potential[MAXN];
    int stack_size;
    int stack_a[4000000];
    int stack_b[4000000];
    int stack_p[4000000];
} UF;

UF uf;
Operation ops[MAXM];
Node* tree[MAXM];
int N, M;
int res[MAXM];
int inconsistent;

void init_uf(int n){
    for(int i=1;i<=n;i++){
        uf.parent[i] = i;
        uf.rank_[i] = 1;
        uf.potential[i] = 0;
    }
    uf.stack_size = 0;
    inconsistent = 0;
}

int find_set(int x){
    if(uf.parent[x] == x) return x;
    int orig_parent = uf.parent[x];
    int root = find_set(orig_parent);
    uf.potential[x] = (uf.potential[x] + uf.potential[orig_parent]) %5;
    uf.parent[x] = root;
    return root;
}

void union_set(int u, int v, int diff){
    int ru = find_set(u);
    int rv = find_set(v);
    if(ru == rv){
        if((uf.potential[v] - uf.potential[u] - diff) %5 !=0){
            inconsistent = 1;
        }
        return;
    }
    if(uf.rank_[ru] < uf.rank_[rv]){
        ru ^= rv;
        rv ^= ru;
        ru ^= rv;
    }
    uf.stack_a[uf.stack_size] = rv;
    uf.stack_b[uf.stack_size] = uf.parent[rv];
    uf.stack_p[uf.stack_size] = uf.potential[rv];
    uf.stack_size++;
    uf.parent[rv] = ru;
    uf.potential[rv] = (uf.potential[u] + diff - uf.potential[v] +5)%5;
    if(uf.rank_[ru] == uf.rank_[rv]){
        uf.rank_[ru]++;
    }
}

void dfs(int u){
    Operation *op = &ops[u];
    // Apply current operation
    if(op->type ==1 || op->type ==2){
        int u_node = op->edge.u;
        int v_node = op->edge.v;
        int diff = (op->type ==1)?1:4;
        union_set(u_node, v_node, diff);
    }
    // Check consistency
    if(inconsistent){
        printf("naive\n");
    }
    else{
        printf("excited\n");
    }
    // Visit children
    Node* child = tree[u];
    while(child){
        dfs(child->idx);
        child = child->next;
    }
    // Undo
    if(op->type ==1 || op->type ==2){
        uf.stack_size -=1;
        uf.parent[op->edge.v] = uf.stack_b[uf.stack_size];
        uf.potential[op->edge.v] = uf.stack_p[uf.stack_size];
        inconsistent = 0;
    }
}

int main(){
    scanf("%d %d", &N, &M);
    for(int i=1;i<=M;i++){
        int k, t;
        scanf("%d %d", &k, &t);
        ops[i].parent = k;
        ops[i].type = t;
        if(t ==1 || t ==2){
            scanf("%d %d", &ops[i].edge.u, &ops[i].edge.v);
        }
        else{
            scanf("%d", &ops[i].edge.u);
        }
        // Build tree
        Node* node = (Node*)malloc(sizeof(Node));
        node->idx = i;
        node->next = tree[k];
        tree[k] = node;
    }
    init_uf(N);
    dfs(0);
    return 0;
}