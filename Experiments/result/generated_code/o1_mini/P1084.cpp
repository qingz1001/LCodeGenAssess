#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAXN 50005
#define INF 9223372036854775807LL

typedef struct Edge {
    int to;
    long long w;
    struct Edge* next;
} Edge;

Edge* adj[MAXN];
long long min_dist[MAXN];
int n, m;
int army[MAXN];
int heap_size = 0;
int heap_nodes[MAXN];
long long heap_dists[MAXN];
int pos_in_heap[MAXN];

// Heap functions
void swap(int a, int b) {
    long long temp_dist = heap_dists[a];
    heap_dists[a] = heap_dists[b];
    heap_dists[b] = temp_dist;

    int temp_node = heap_nodes[a];
    heap_nodes[a] = heap_nodes[b];
    heap_nodes[b] = temp_node;

    pos_in_heap[heap_nodes[a]] = a;
    pos_in_heap[heap_nodes[b]] = b;
}

void heapify_up(int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap_dists[i] < heap_dists[parent]) {
            swap(i, parent);
            i = parent;
        }
        else {
            break;
        }
    }
}

void heapify_down(int i) {
    while (1) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < heap_size && heap_dists[left] < heap_dists[smallest]) {
            smallest = left;
        }
        if (right < heap_size && heap_dists[right] < heap_dists[smallest]) {
            smallest = right;
        }
        if (smallest != i) {
            swap(i, smallest);
            i = smallest;
        }
        else {
            break;
        }
    }
}

void push(int node, long long dist) {
    heap_nodes[heap_size] = node;
    heap_dists[heap_size] = dist;
    pos_in_heap[node] = heap_size;
    heapify_up(heap_size);
    heap_size++;
}

int pop() {
    if (heap_size == 0) return -1;
    int top = heap_nodes[0];
    heap_size--;
    if (heap_size > 0) {
        heap_nodes[0] = heap_nodes[heap_size];
        heap_dists[0] = heap_dists[heap_size];
        pos_in_heap[heap_nodes[0]] = 0;
        heapify_down(0);
    }
    pos_in_heap[top] = -1;
    return top;
}

int empty() {
    return heap_size == 0;
}

int main(){
    scanf("%d", &n);
    for(int i=0;i<n-1;i++){
        int u, v;
        long long w;
        scanf("%d %d %lld", &u, &v, &w);
        Edge* edge1 = (Edge*)malloc(sizeof(Edge));
        edge1->to = v;
        edge1->w = w;
        edge1->next = adj[u];
        adj[u] = edge1;
        Edge* edge2 = (Edge*)malloc(sizeof(Edge));
        edge2->to = u;
        edge2->w = w;
        edge2->next = adj[v];
        adj[v] = edge2;
    }
    scanf("%d", &m);
    for(int i=0;i<m;i++) scanf("%d", &army[i]);
    for(int i=1;i<=n;i++) min_dist[i] = INF;
    memset(pos_in_heap, -1, sizeof(pos_in_heap));
    // Initialize heap with army positions
    for(int i=0;i<m;i++){
        int node = army[i];
        if(min_dist[node] > 0){
            min_dist[node] = 0;
            push(node, 0);
        }
    }
    // Dijkstra
    while(!empty()){
        int u = pop();
        Edge* e = adj[u];
        while(e){
            int v = e->to;
            if(min_dist[v] > min_dist[u] + e->w){
                min_dist[v] = min_dist[u] + e->w;
                if(pos_in_heap[v] == -1){
                    push(v, min_dist[v]);
                }
                else{
                    int idx = pos_in_heap[v];
                    heap_dists[idx] = min_dist[v];
                    heapify_up(idx);
                    heapify_down(idx);
                }
            }
            e = e->next;
        }
    }
    // Binary search
    long long left = 0, right = 50000000000000000LL;
    long long answer = -1;
    // Find maximum distance
    for(int i=1;i<=n;i++) if(min_dist[i] < INF && min_dist[i] > right) right = min_dist[i];
    // Function to check coverage
    // Implemented as a nested function using explicit stack
    // To avoid recursion depth issues
    int is_possible(long long T, int *required){
        int stack_size = 0;
        int stack[MAXN];
        int state[MAXN]; // 0: not processed, 1: processed
        memset(state, 0, sizeof(state));
        int checkpoints = 0;
        stack[stack_size++] = 1;
        while(stack_size > 0){
            int u = stack[--stack_size];
            if(u < 0){
                u = -u;
                // Post-processing
                int need = 0;
                Edge* e = adj[u];
                while(e){
                    if(e->to != 1 && state[e->to] == 2){
                        need = 1;
                    }
                    e = e->next;
                }
                if(need){
                    if(min_dist[u] <= T){
                        checkpoints++;
                        state[u] = 1;
                    }
                    else{
                        state[u] = 2;
                    }
                }
                else{
                    state[u] = 0;
                }
            }
            else{
                stack[stack_size++] = -u; // Mark for post-processing
                Edge* e = adj[u];
                while(e){
                    if(e->to != 1 && e->to != u){
                        stack[stack_size++] = e->to;
                    }
                    e = e->next;
                }
            }
        }
        *required = checkpoints;
        return 1;
    }
    // Implement the coverage check with DFS
    // Rewriting the check function properly
    int check(long long T, int *required_chk){
        // Implement DFS and place checkpoints greedily
        struct StackNode {
            int node;
            int parent;
            int state; // 0: visit children, 1: process node
        } stack_nodes[MAXN];
        int top = 0;
        stack_nodes[top].node = 1;
        stack_nodes[top].parent = -1;
        stack_nodes[top].state = 0;
        top++;
        int checkpoints = 0;
        int covered[MAXN];
        memset(covered, 0, sizeof(covered));
        while(top > 0){
            top--;
            struct StackNode current = stack_nodes[top];
            int u = current.node;
            if(current.state == 0){
                // Push back for processing after children
                stack_nodes[top].node = u;
                stack_nodes[top].parent = current.parent;
                stack_nodes[top].state = 1;
                top++;
                // Push children
                Edge* e = adj[u];
                while(e){
                    if(e->to != current.parent){
                        stack_nodes[top].node = e->to;
                        stack_nodes[top].parent = u;
                        stack_nodes[top].state = 0;
                        top++;
                    }
                    e = e->next;
                }
            }
            else{
                // Process node after children
                int need_checkpoint = 0;
                Edge* e = adj[u];
                int is_leaf = 1;
                while(e){
                    if(e->to != current.parent){
                        is_leaf = 0;
                        if(!covered[e->to]){
                            need_checkpoint = 1;
                        }
                    }
                    e = e->next;
                }
                if(is_leaf){
                    // Leaf must be covered by some ancestor
                    // Do nothing here, handled by parent
                }
                if(need_checkpoint){
                    if(u != 1 && min_dist[u] <= T){
                        checkpoints++;
                        covered[u] = 1;
                    }
                }
                // If any child has a checkpoint, this node is covered
                e = adj[u];
                while(e){
                    if(e->to != current.parent){
                        if(covered[e->to]){
                            covered[u] = 1;
                        }
                    }
                    e = e->next;
                }
            }
        }
        *required_chk = checkpoints;
        return 1;
    }
    // Binary search with proper check
    while(left <= right){
        long long mid = left + (right - left) / 2;
        int required = 0;
        check(mid, &required);
        // Now verify coverage
        // Implement the correct coverage check
        // Reset covered
        // Implement another DFS
        // Implemented above in `check` function
        if(required <= m){
            answer = mid;
            right = mid - 1;
        }
        else{
            left = mid + 1;
        }
    }
    // Now, verify if answer is valid
    if(answer != -1){
        // Check if with answer, all leaves are covered
        // Implement the check again
        int required_final = 0;
        check(answer, &required_final);
        if(required_final <= m){
            printf("%lld\n", answer);
            return 0;
        }
    }
    printf("-1\n");
    return 0;
}