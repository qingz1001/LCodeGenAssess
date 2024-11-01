#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int minv;
    int lazy;
} Node;

int n, q;
Node *tree_nodes;

void build(int node, int l, int r){
    tree_nodes[node].lazy = 0;
    if(l == r){
        tree_nodes[node].minv = 1;
        return;
    }
    int mid = (l + r) / 2;
    build(2*node, l, mid);
    build(2*node+1, mid+1, r);
    if(tree_nodes[2*node].minv < tree_nodes[2*node+1].minv){
        tree_nodes[node].minv = tree_nodes[2*node].minv;
    }
    else{
        tree_nodes[node].minv = tree_nodes[2*node+1].minv;
    }
}

void pushdown(int node, int l, int r){
    if(tree_nodes[node].lazy){
        int mid = (l + r) / 2;
        // Left child
        if(tree_nodes[2*node].minv < tree_nodes[node].lazy){
            tree_nodes[2*node].minv = tree_nodes[node].lazy;
            if(tree_nodes[2*node].lazy < tree_nodes[node].lazy){
                tree_nodes[2*node].lazy = tree_nodes[node].lazy;
            }
        }
        // Right child
        if(tree_nodes[2*node+1].minv < tree_nodes[node].lazy){
            tree_nodes[2*node+1].minv = tree_nodes[node].lazy;
            if(tree_nodes[2*node+1].lazy < tree_nodes[node].lazy){
                tree_nodes[2*node+1].lazy = tree_nodes[node].lazy;
            }
        }
        tree_nodes[node].lazy = 0;
    }
}

int range_min_query(int node, int l, int r, int ql, int qr){
    if(ql > r || qr < l){
        return INT32_MAX;
    }
    if(ql <= l && r <= qr){
        return tree_nodes[node].minv;
    }
    pushdown(node, l, r);
    int mid = (l + r) / 2;
    int left_min = range_min_query(2*node, l, mid, ql, qr);
    int right_min = range_min_query(2*node+1, mid+1, r, ql, qr);
    return left_min < right_min ? left_min : right_min;
}

void range_max_update(int node, int l, int r, int ql, int qr, int x){
    if(ql > r || qr < l){
        return;
    }
    if(ql <= l && r <= qr){
        if(tree_nodes[node].minv >= x){
            return;
        }
        if(l == r){
            if(tree_nodes[node].minv < x){
                tree_nodes[node].minv = x;
            }
            return;
        }
    }
    pushdown(node, l, r);
    int mid = (l + r) / 2;
    range_max_update(2*node, l, mid, ql, qr, x);
    range_max_update(2*node+1, mid+1, r, ql, qr, x);
    tree_nodes[node].minv = tree_nodes[2*node].minv < tree_nodes[2*node+1].minv ? tree_nodes[2*node].minv : tree_nodes[2*node+1].minv;
}

int main(){
    if(scanf("%d %d", &n, &q)!=2){
        return 0;
    }
    tree_nodes = (Node*)malloc(sizeof(Node)*4*(n+2));
    build(1, 1, n);
    int l, r, x;
    for(int i=1;i<=q;i++){
        if(scanf("%d %d %d", &l, &r, &x)!=3){
            free(tree_nodes);
            return 0;
        }
        int current_min = range_min_query(1, 1, n, l, r);
        if(current_min > x){
            printf("%d", i);
            free(tree_nodes);
            return 0;
        }
        range_max_update(1, 1, n, l, r, x);
    }
    printf("0");
    free(tree_nodes);
    return 0;
}