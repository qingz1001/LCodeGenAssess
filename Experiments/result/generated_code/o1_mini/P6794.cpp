#include <stdio.h>
#include <stdlib.h>

// Define maximum number of nodes for the segment trees
#define MAXNODES 4000000

typedef struct Node {
    long long val;
    int left;
    int right;
} Node;

Node nodes[MAXNODES];
int node_cnt = 0;

// Function to create a new node
int new_node() {
    nodes[node_cnt].val = 0;
    nodes[node_cnt].left = -1;
    nodes[node_cnt].right = -1;
    return node_cnt++;
}

// Build initial segment tree
int build(int l, int r, long long* arr) {
    int root = new_node();
    if (l == r) {
        nodes[root].val = arr[l];
        return root;
    }
    int mid = (l + r) / 2;
    nodes[root].left = build(l, mid, arr);
    nodes[root].right = build(mid + 1, r, arr);
    return root;
}

// Update the segment tree persistently
int update(int prev, int l, int r, int pos, long long value) {
    int root = new_node();
    nodes[root].val = nodes[prev].val;
    nodes[root].left = nodes[prev].left;
    nodes[root].right = nodes[prev].right;
    if (l == r) {
        nodes[root].val = value;
        return root;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) {
        nodes[root].left = update(nodes[prev].left, l, mid, pos, value);
    }
    else {
        nodes[root].right = update(nodes[prev].right, mid + 1, r, pos, value);
    }
    return root;
}

// Query the segment tree
long long query(int root, int l, int r, int pos) {
    if (l == r) return nodes[root].val;
    int mid = (l + r) / 2;
    if (pos <= mid) return query(nodes[root].left, l, mid, pos);
    else return query(nodes[root].right, mid + 1, r, pos);
}

int main(){
    int n, q;
    scanf("%d %d", &n, &q);
    long long* initial_barriers = (long long*)malloc((n) * sizeof(long long));
    for(int i=1;i<n;i++) scanf("%lld", &initial_barriers[i]);
    // Initialize barrier segment trees for version 0
    int barrier_roots[200005];
    barrier_roots[0] = build(1, n-1, initial_barriers);
    // Initialize water levels to 0
    long long* initial_water = (long long*)calloc((n+1), sizeof(long long));
    int water_roots[200005];
    water_roots[0] = build(1, n, initial_water);
    free(initial_water);
    // Process operations
    for(int op=1; op<=q; op++){
        int type;
        scanf("%d", &type);
        if(type == 0){
            int parent, x;
            long long h;
            scanf("%d %d %lld", &parent, &x, &h);
            // Update water level to max(current, h)
            long long current = query(water_roots[parent], 1, n, x);
            long long new_val = current >= h ? current : h;
            water_roots[op] = update(water_roots[parent], 1, n, x, new_val);
            barrier_roots[op] = barrier_roots[parent];
        }
        else if(type == 1){
            int parent, x;
            scanf("%d %d", &parent, &x);
            // Drain water: set to 0
            water_roots[op] = update(water_roots[parent], 1, n, x, 0);
            barrier_roots[op] = barrier_roots[parent];
        }
        else if(type == 2){
            int parent, x;
            long long h;
            scanf("%d %d %lld", &parent, &x, &h);
            // Update barrier to max(current, h)
            long long current = query(barrier_roots[parent], 1, n-1, x);
            long long new_val = current >= h ? current : h;
            barrier_roots[op] = update(barrier_roots[parent], 1, n-1, x, new_val);
            water_roots[op] = water_roots[parent];
        }
        else if(type == 3){
            int parent, x;
            scanf("%d %d", &parent, &x);
            long long res = query(water_roots[parent], 1, n, x);
            printf("%lld\n", res);
            // For query, version doesn't change
            barrier_roots[op] = barrier_roots[parent];
            water_roots[op] = water_roots[parent];
        }
    }
    return 0;
}