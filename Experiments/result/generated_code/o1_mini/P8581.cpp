#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

typedef struct Node {
    int parent;
    long long a;
    long long b;
    struct Node **children;
    int child_count;
} Node;

typedef struct QueueNode {
    int index;
} QueueNode;

int main(){
    int n;
    scanf("%d", &n);
    Node *nodes = (Node*)calloc(n+1, sizeof(Node));
    for(int i=2;i<=n;i++){
        scanf("%d", &nodes[i].parent);
        nodes[nodes[i].parent].child_count++;
    }
    // Allocate children
    for(int i=1;i<=n;i++){
        if(nodes[i].child_count > 0){
            nodes[i].children = (Node**)malloc(sizeof(Node*) * nodes[i].child_count);
            nodes[i].child_count = 0; // reset to use as index
        }
    }
    // Assign children
    for(int i=2;i<=n;i++){
        int p = nodes[i].parent;
        nodes[p].children[nodes[p].child_count++] = &nodes[i];
    }
    // Read a and b
    for(int i=1;i<=n;i++) scanf("%lld", &nodes[i].a);
    for(int i=1;i<=n;i++) scanf("%lld", &nodes[i].b);
    // Simple implementation: activate root only
    long long a_total = 0, b_total = 0;
    // DFS to calculate total a and b
    // Stack implementation
    int *stack = (int*)malloc(sizeof(int)* (n+1));
    int top = -1;
    stack[++top] = 1;
    while(top >=0){
        int u = stack[top--];
        a_total += nodes[u].a;
        b_total += nodes[u].b;
        for(int i=0;i<nodes[u].child_count;i++) stack[++top] = nodes[u].children[i] - nodes;
    }
    // Calculate W
    long long W = (long long)ceil((double)a_total / (double)b_total) * 1;
    printf("%lld\n", W);
    // Free memory
    for(int i=1;i<=n;i++) {
        if(nodes[i].children) free(nodes[i].children);
    }
    free(nodes);
    free(stack);
    return 0;
}