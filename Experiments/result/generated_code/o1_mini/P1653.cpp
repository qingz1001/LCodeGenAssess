#include <stdio.h>
#include <stdlib.h>

#define MAXN 250000
#define MAXM 1000000

typedef struct {
    int *data;
    int top;
    int size;
} Stack;

void initStack(Stack *s, int size) {
    s->data = (int*)malloc(sizeof(int) * size);
    s->top = -1;
    s->size = size;
}

void push(Stack *s, int val) {
    s->data[++(s->top)] = val;
}

int pop(Stack *s) {
    return s->data[(s->top)--];
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int main(){
    int W, L;
    scanf("%d %d", &W, &L);
    int N = W * L;
    int *H = (int*)malloc(sizeof(int) * N);
    for(int i=0;i<L;i++) {
        for(int j=0;j<W;j++) {
            H[i*W+j] = 0;
        }
    }
    for(int i=0;i<L;i++) {
        for(int j=0;j<W;j++) {
            scanf("%d", &H[i*W+j]);
        }
    }
    // Build adjacency list
    int *adj = (int*)malloc(sizeof(int) * 4 * N);
    int *adj_start = (int*)calloc(N, sizeof(int));
    int *adj_count = (int*)calloc(N, sizeof(int));
    // First, count the number of edges per node
    for(int i=0;i<L;i++) {
        for(int j=0;j<W;j++) {
            int id = i*W + j;
            // Up
            if(i > 0){
                int ni = (i-1)*W + j;
                if(H[id] >= H[ni]){
                    adj_count[id]++;
                }
            }
            // Down
            if(i < L-1){
                int ni = (i+1)*W + j;
                if(H[id] >= H[ni]){
                    adj_count[id]++;
                }
            }
            // Left
            if(j > 0){
                int ni = i*W + (j-1);
                if(H[id] >= H[ni]){
                    adj_count[id]++;
                }
            }
            // Right
            if(j < W-1){
                int ni = i*W + (j+1);
                if(H[id] >= H[ni]){
                    adj_count[id]++;
                }
            }
        }
    }
    // Fill adj_start
    adj_start[0] = 0;
    for(int i=1;i<N;i++) {
        adj_start[i] = adj_start[i-1] + adj_count[i-1];
    }
    // Reset adj_count to use as current index
    for(int i=0;i<N;i++) adj_count[i] = 0;
    // Populate adj
    for(int i=0;i<L;i++) {
        for(int j=0;j<W;j++) {
            int id = i*W + j;
            // Up
            if(i > 0){
                int ni = (i-1)*W + j;
                if(H[id] >= H[ni]){
                    adj[adj_start[id] + adj_count[id]++] = ni;
                }
            }
            // Down
            if(i < L-1){
                int ni = (i+1)*W + j;
                if(H[id] >= H[ni]){
                    adj[adj_start[id] + adj_count[id]++] = ni;
                }
            }
            // Left
            if(j > 0){
                int ni = i*W + (j-1);
                if(H[id] >= H[ni]){
                    adj[adj_start[id] + adj_count[id]++] = ni;
                }
            }
            // Right
            if(j < W-1){
                int ni = i*W + (j+1);
                if(H[id] >= H[ni]){
                    adj[adj_start[id] + adj_count[id]++] = ni;
                }
            }
        }
    }
    // Build transpose adjacency list
    int *transpose = (int*)malloc(sizeof(int) * 4 * N);
    int *transpose_start = (int*)calloc(N, sizeof(int));
    int *transpose_count = (int*)calloc(N, sizeof(int));
    // Count transpose edges
    for(int u=0; u<N; u++) {
        for(int k=0; k<adj_count[u]; k++) {
            int v = adj[adj_start[u] + k];
            transpose_count[v]++;
        }
    }
    // Fill transpose_start
    transpose_start[0] = 0;
    for(int i=1;i<N;i++) {
        transpose_start[i] = transpose_start[i-1] + transpose_count[i-1];
    }
    // Reset transpose_count
    for(int i=0;i<N;i++) transpose_count[i] = 0;
    // Populate transpose
    for(int u=0; u<N; u++) {
        for(int k=0; k<adj_count[u]; k++) {
            int v = adj[adj_start[u] + k];
            transpose[transpose_start[v] + transpose_count[v]++] = u;
        }
    }
    // First pass: DFS on original graph to get finish order
    char *visited = (char*)calloc(N, sizeof(char));
    Stack stack_order;
    initStack(&stack_order, N);
    Stack dfs_stack;
    initStack(&dfs_stack, N);
    for(int u=0; u<N; u++) {
        if(!visited[u]){
            push(&dfs_stack, u);
            while(!isEmpty(&dfs_stack)){
                int curr = pop(&dfs_stack);
                if(curr >= 0){
                    if(!visited[curr]){
                        visited[curr] = 1;
                        push(&dfs_stack, ~curr);
                        for(int k=0; k<adj_count[curr]; k++) {
                            int v = adj[adj_start[curr] + k];
                            if(!visited[v]){
                                push(&dfs_stack, v);
                            }
                        }
                    }
                }
                else {
                    push(&stack_order, ~curr);
                }
            }
        }
    }
    free(dfs_stack.data);
    free(visited);
    // Second pass: DFS on transpose graph
    int *component = (int*)malloc(sizeof(int) * N);
    for(int i=0;i<N;i++) component[i] = -1;
    int cid = 0;
    Stack stack_dfs;
    initStack(&stack_dfs, N);
    while(!isEmpty(&stack_order)){
        int u = pop(&stack_order);
        if(component[u] == -1){
            push(&stack_dfs, u);
            while(!isEmpty(&stack_dfs)){
                int curr = pop(&stack_dfs);
                if(curr >= 0){
                    if(component[curr] == -1){
                        component[curr] = cid;
                        push(&stack_dfs, ~curr);
                        for(int k=0; k<transpose_count[curr]; k++) {
                            int v = transpose[transpose_start[curr] + k];
                            if(component[v] == -1){
                                push(&stack_dfs, v);
                            }
                        }
                    }
                }
            }
        }
    }
    free(stack_order.data);
    free(stack_dfs.data);
    // Build condensation DAG
    int num_components = cid;
    int *in_deg = (int*)calloc(num_components, sizeof(int));
    int *out_deg = (int*)calloc(num_components, sizeof(int));
    for(int u=0; u<N; u++) {
        for(int k=0; k<adj_count[u]; k++) {
            int v = adj[adj_start[u] + k];
            if(component[u] != component[v]){
                out_deg[component[u]]++;
                in_deg[component[v]]++;
            }
        }
    }
    // Count sources and sinks
    int sources=0, sinks=0;
    for(int i=0;i<num_components;i++) {
        if(in_deg[i]==0) sources++;
        if(out_deg[i]==0) sinks++;
    }
    if(num_components == 1){
        printf("0\n");
    }
    else{
        if(sources > sinks) printf("%d\n", sources);
        else printf("%d\n", sinks);
    }
    // Free memory
    free(H);
    free(adj);
    free(adj_start);
    free(adj_count);
    free(transpose);
    free(transpose_start);
    free(transpose_count);
    free(component);
    free(in_deg);
    free(out_deg);
    return 0;
}