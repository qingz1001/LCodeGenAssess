#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int idx;
    int depth;
} Node;

// Compare function for sorting nodes by descending depth and ascending index
int compare_nodes(const void *a, const void *b) {
    Node *nodeA = (Node *)a;
    Node *nodeB = (Node *)b;
    if (nodeA->depth != nodeB->depth)
        return nodeB->depth - nodeA->depth;
    return nodeA->idx - nodeB->idx;
}

// Compare function for sorting integers in descending order
int compare_desc(const void *a, const void *b) {
    int valA = *(int *)a;
    int valB = *(int *)b;
    if(valB != valA)
        return valB - valA;
    return 0;
}

int main(){
    int n;
    double k;
    scanf("%d %lf", &n, &k);
    int *d = (int*)malloc(n * sizeof(int));
    for(int i=0;i<n;i++) scanf("%d", &d[i]);

    // Compute parent for each node
    int *parent = (int*)calloc(n+1, sizeof(int)); // 1-based
    for(int i=1;i<=n;i++){
        double div = (double)i / k;
        int p = (int)floor(div);
        parent[i] = p;
    }

    // Count children for each node
    int *child_count = (int*)calloc(n+1, sizeof(int));
    for(int i=1;i<=n;i++) {
        if(parent[i] !=0){
            child_count[parent[i]]++;
        }
    }

    // Compute child_ptr
    int *child_ptr = (int*)calloc(n+1, sizeof(int));
    child_ptr[1] = 0;
    for(int i=2;i<=n;i++) {
        child_ptr[i] = child_ptr[i-1] + child_count[i-1];
    }

    // Allocate children array
    int total_children = child_ptr[n] + child_count[n];
    int *children = (int*)malloc(total_children * sizeof(int));

    // Reset child_count for assignment
    for(int i=1;i<=n;i++) child_count[i]=0;

    // Assign children
    for(int i=1;i<=n;i++) {
        if(parent[i] !=0){
            children[child_ptr[parent[i]] + child_count[parent[i]]] = i;
            child_count[parent[i]]++;
        }
    }

    // Compute depth using BFS
    int *depth = (int*)calloc(n+1, sizeof(int)); // 1-based
    Node *queue = (Node*)malloc(n * sizeof(Node));
    int front =0, rear=0;

    // Enqueue root nodes
    for(int i=1;i<=n;i++) {
        if(parent[i]==0){
            depth[i]=1;
            queue[rear].idx = i;
            queue[rear].depth = 1;
            rear++;
        }
    }

    while(front < rear){
        Node current = queue[front++];
        int u = current.idx;
        for(int i=child_ptr[u]; i < child_ptr[u] + child_count[u]; i++){
            int v = children[i];
            depth[v] = depth[u] +1;
            queue[rear].idx = v;
            queue[rear].depth = depth[v];
            rear++;
        }
    }

    // Create node array
    Node *nodes = (Node*)malloc(n * sizeof(Node));
    for(int i=1;i<=n;i++){
        nodes[i-1].idx = i;
        nodes[i-1].depth = depth[i];
    }

    // Sort nodes by descending depth and ascending index
    qsort(nodes, n, sizeof(Node), compare_nodes);

    // Sort d in descending order
    qsort(d, n, sizeof(int), compare_desc);

    // Assign sorted d to sorted nodes
    int *assign = (int*)malloc((n+1) * sizeof(int)); // 1-based
    for(int i=0;i<n;i++) {
        assign[nodes[i].idx] = d[i];
    }

    // Print the assignment
    for(int i=1;i<=n;i++) {
        printf("%d%c", assign[i], (i==n)?'\n':' ');
    }

    // Free allocated memory
    free(d);
    free(parent);
    free(child_count);
    free(child_ptr);
    free(children);
    free(depth);
    free(queue);
    free(nodes);
    free(assign);
    
    return 0;
}