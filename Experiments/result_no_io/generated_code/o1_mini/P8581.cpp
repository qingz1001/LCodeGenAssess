#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef long long ll;

typedef struct Node {
    int id;
    ll a;
    ll b;
    ll ceil_r;
    struct Node** children;
    int child_count;
} Node;

// Comparison function for sorting nodes based on ceil_r ascending
int cmp(const void* a, const void* b){
    ll r1 = (*(Node**)a)->ceil_r;
    ll r2 = (*(Node**)b)->ceil_r;
    if(r1 != r2){
        return (r1 < r2) ? -1 : 1;
    }
    return 0;
}

int main(){
    int n;
    scanf("%d", &n);
    
    // Allocate nodes
    Node* nodes = (Node*)malloc((n+1) * sizeof(Node));
    for(int i=1;i<=n;i++){
        nodes[i].id = i;
        nodes[i].children = NULL;
        nodes[i].child_count = 0;
    }
    
    // Read parent array
    int parent;
    for(int i=2;i<=n;i++){
        scanf("%d", &parent);
        nodes[parent].child_count++;
    }
    
    // Allocate children arrays
    for(int i=1;i<=n;i++){
        if(nodes[i].child_count > 0){
            nodes[i].children = (Node**)malloc(nodes[i].child_count * sizeof(Node*));
            nodes[i].child_count = 0; // reset to use as index
        }
    }
    
    // Read parent array again to assign children
    rewind(stdin);
    // Skip first line
    scanf("%d", &n);
    for(int i=2;i<=n;i++){
        scanf("%d", &parent);
        nodes[parent].children[nodes[parent].child_count++] = &nodes[i];
    }
    
    // Read a_i
    for(int i=1;i<=n;i++) {
        scanf("%lld", &nodes[i].a);
    }
    
    // Read b_i
    for(int i=1;i<=n;i++) {
        scanf("%lld", &nodes[i].b);
    }
    
    // Calculate ceil_r for each node
    for(int i=1;i<=n;i++){
        double r = (double)nodes[i].a / nodes[i].b;
        nodes[i].ceil_r = (ll)ceil(r);
    }
    
    // To minimize W, activate nodes in order of increasing ceil_r
    // and multiply by activation order
    // Sort all nodes based on ceil_r
    Node** node_ptrs = (Node**)malloc(n * sizeof(Node*));
    for(int i=0;i<n;i++) node_ptrs[i] = &nodes[i+1];
    qsort(node_ptrs, n, sizeof(Node*), cmp);
    
    // Calculate W
    ll W = 0;
    for(int i=0;i<n;i++){
        W += (ll)(i+1) * node_ptrs[i]->ceil_r;
    }
    
    printf("%lld", W);
    
    // Free memory
    for(int i=1;i<=n;i++) {
        if(nodes[i].children != NULL){
            free(nodes[i].children);
        }
    }
    free(nodes);
    free(node_ptrs);
    
    return 0;
}