#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int node;
    int type;
    int next;
} Edge;

typedef struct {
    int diff;
    int entry;
} NodeInfo;

typedef struct {
    int node;
    int state;
} StackItem;

// Comparison function for qsort: first by diff, then by entry
int compare(const void *a, const void *b) {
    NodeInfo *na = (NodeInfo *)a;
    NodeInfo *nb = (NodeInfo *)b;
    if (na->diff != nb->diff)
        return na->diff - nb->diff;
    return na->entry - nb->entry;
}

// Binary search to find the first index where sorted_nodes[idx].diff >= d
int find_first(int N, NodeInfo *sorted_nodes, int d) {
    int left = 0, right = N;
    while(left < right){
        int mid = left + (right - left)/2;
        if(sorted_nodes[mid].diff < d){
            left = mid +1;
        }
        else{
            right = mid;
        }
    }
    return left;
}

// Binary search to find the first index where sorted_nodes[idx].diff > d
int find_last(int N, NodeInfo *sorted_nodes, int d) {
    int left = 0, right = N;
    while(left < right){
        int mid = left + (right - left)/2;
        if(sorted_nodes[mid].diff <= d){
            left = mid +1;
        }
        else{
            right = mid;
        }
    }
    return left;
}

// Binary search to find the first index in [left, right) where entry >= e_l
int lower_bound_entry(int left, int right, int e_l, NodeInfo *sorted_nodes) {
    while(left < right){
        int mid = left + (right - left)/2;
        if(sorted_nodes[mid].entry < e_l){
            left = mid +1;
        }
        else{
            right = mid;
        }
    }
    return left;
}

// Binary search to find the first index in [left, right) where entry > ex_l
int upper_bound_entry(int left, int right, int ex_l, NodeInfo *sorted_nodes) {
    while(left < right){
        int mid = left + (right - left)/2;
        if(sorted_nodes[mid].entry <= ex_l){
            left = mid +1;
        }
        else{
            right = mid;
        }
    }
    return left;
}

int main(){
    int N;
    scanf("%d", &N);
    // Initialize adjacency list
    // Using edge list with head pointers
    int max_edges = 2*N;
    Edge *edges = (Edge *)malloc(sizeof(Edge) * max_edges);
    int *adj_head = (int *)malloc(sizeof(int) * (N+1));
    for(int i=1;i<=N;i++) adj_head[i]=-1;
    int edge_cnt=0;
    for(int i=0;i<N-1;i++){
        int a, b, t;
        scanf("%d %d %d", &a, &b, &t);
        edges[edge_cnt].node = b;
        edges[edge_cnt].type = t;
        edges[edge_cnt].next = adj_head[a];
        adj_head[a] = edge_cnt++;
        edges[edge_cnt].node = a;
        edges[edge_cnt].type = t;
        edges[edge_cnt].next = adj_head[b];
        adj_head[b] = edge_cnt++;
    }
    // Initialize DFS variables
    int *entry_time = (int *)malloc(sizeof(int)*(N+1));
    int *exit_time = (int *)malloc(sizeof(int)*(N+1));
    int *diff = (int *)malloc(sizeof(int)*(N+1));
    for(int i=1;i<=N;i++) diff[i]=0;
    // Iterative DFS
    StackItem *stack_arr = (StackItem *)malloc(sizeof(StackItem)* (N*2));
    int top =0;
    stack_arr[top].node =1;
    stack_arr[top].state =0;
    top++;
    int timer=0;
    int *parent = (int *)malloc(sizeof(int)*(N+1));
    parent[1] = -1;
    while(top >0){
        StackItem current = stack_arr[--top];
        int node = current.node;
        if(current.state ==0){
            entry_time[node] = ++timer;
            // Push exit marker
            stack_arr[top].node = node;
            stack_arr[top].state =1;
            top++;
            // Push children
            int e = adj_head[node];
            while(e != -1){
                int child = edges[e].node;
                int type = edges[e].type;
                if(child != parent[node]){
                    parent[child] = node;
                    diff[child] = diff[node] + (type ==0 ? 1 : -1);
                    stack_arr[top].node = child;
                    stack_arr[top].state =0;
                    top++;
                }
                e = edges[e].next;
            }
        }
        else{
            exit_time[node] = timer;
        }
    }
    // Create sorted_nodes array
    NodeInfo *sorted_nodes = (NodeInfo *)malloc(sizeof(NodeInfo)*N);
    for(int i=1;i<=N;i++){
        sorted_nodes[i-1].diff = diff[i];
        sorted_nodes[i-1].entry = entry_time[i];
    }
    // Sort the sorted_nodes
    qsort(sorted_nodes, N, sizeof(NodeInfo), compare);
    // Calculate the answer
    unsigned long long answer=0;
    for(int i=1;i<=N;i++){
        int d = diff[i];
        int e_l = entry_time[i];
        int ex_l = exit_time[i];
        // Find the range of sorted_nodes with diff == d
        int first = find_first(N, sorted_nodes, d);
        int last = find_last(N, sorted_nodes, d);
        if(first == last) continue;
        // Within [first, last), find entries between e_l and ex_l
        int lb = lower_bound_entry(first, last, e_l, sorted_nodes);
        int ub = upper_bound_entry(first, last, ex_l, sorted_nodes);
        int cnt = ub - lb;
        if(cnt >=2){
            answer += ((unsigned long long)cnt * (cnt -1))/2;
        }
    }
    printf("%llu\n", answer);
    // Free memory
    free(edges);
    free(adj_head);
    free(entry_time);
    free(exit_time);
    free(diff);
    free(stack_arr);
    free(parent);
    free(sorted_nodes);
    return 0;
}