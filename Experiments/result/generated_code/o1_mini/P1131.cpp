#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Maximum number of nodes
#define MAXN 500005

typedef struct {
    int to;
    int t;
    int next;
} Edge;

Edge edges[1000005];
int head[MAXN];
int edge_cnt = 0;

// Function to add edge to adjacency list
void add_edge(int from, int to, int t){
    edges[edge_cnt].to = to;
    edges[edge_cnt].t = t;
    edges[edge_cnt].next = head[from];
    head[from] = edge_cnt++;
}

// Queue for BFS
typedef struct {
    int data[MAXN];
    int front, rear;
} Queue;

void enqueue(Queue *q, int x){
    q->data[q->rear++] = x;
}

int dequeue(Queue *q){
    return q->data[q->front++];
}

int is_empty(Queue *q){
    return q->front >= q->rear;
}

int main(){
    int N, S;
    scanf("%d", &N);
    scanf("%d", &S);

    // Initialize head
    for(int i=1;i<=N;i++) head[i]=-1;

    // Degree array
    int degree[N+1];
    memset(degree, 0, sizeof(degree));

    // Read edges
    for(int i=0;i<N-1;i++){
        int a, b, t;
        scanf("%d %d %d", &a, &b, &t);
        add_edge(a, b, t);
        add_edge(b, a, t);
        degree[a]++;
        degree[b]++;
    }

    // BFS to compute distances
    long long dist[N+1];
    for(int i=1;i<=N;i++) dist[i] = -1;
    Queue q;
    q.front = q.rear = 0;
    enqueue(&q, S);
    dist[S] = 0;
    while(!is_empty(&q)){
        int u = dequeue(&q);
        for(int e = head[u]; e != -1; e = edges[e].next){
            int v = edges[e].to;
            if(dist[v]==-1){
                dist[v] = dist[u] + edges[e].t;
                enqueue(&q, v);
            }
        }
    }

    // Identify terminal nodes and find max_dist
    long long max_dist = 0;
    int is_terminal[N+1];
    memset(is_terminal, 0, sizeof(is_terminal));
    for(int i=1;i<=N;i++){
        if( (degree[i]==1 && i != S) || (N==1 && i == S)) {
            is_terminal[i] = 1;
            if(dist[i] > max_dist){
                max_dist = dist[i];
            }
        }
    }

    // Compute D[node] = max_dist - dist[node] for terminal nodes
    long long D[MAXN];
    for(int i=1;i<=N;i++) D[i] = 0;
    for(int i=1;i<=N;i++) {
        if(is_terminal[i]){
            D[i] = max_dist - dist[i];
        }
    }

    // Iterative DFS for post-order traversal
    // Stack elements: node, state
    typedef struct {
        int node;
        int state;
    } StackNode;

    StackNode stack_nodes[2*MAXN];
    int top = 0;
    stack_nodes[top].node = S;
    stack_nodes[top].state = 0;
    top++;
    
    // Parent array
    int parent_node[N+1];
    memset(parent_node, -1, sizeof(parent_node));
    // To store D_res
    long long D_res[MAXN];
    for(int i=1;i<=N;i++) D_res[i]=0;

    while(top > 0){
        StackNode current = stack_nodes[--top];
        int u = current.node;
        if(current.state == 0){
            // Push back with state=1
            stack_nodes[top].node = u;
            stack_nodes[top].state = 1;
            top++;
            // Push children
            for(int e = head[u]; e != -1; e = edges[e].next){
                int v = edges[e].to;
                if(v != parent_node[u]){
                    parent_node[v] = u;
                    stack_nodes[top].node = v;
                    stack_nodes[top].state = 0;
                    top++;
                }
            }
        }
        else{
            // Process node u
            long long max_child = 0;
            for(int e = head[u]; e != -1; e = edges[e].next){
                int v = edges[e].to;
                if(v != parent_node[u]){
                    if(D_res[v] > max_child){
                        max_child = D_res[v];
                    }
                }
            }
            if(D[u] > max_child){
                D_res[u] = D[u];
            }
            else{
                D_res[u] = max_child;
            }
        }
    }

    // Compute the total sum
    long long total = 0;
    for(int i=1;i<=N;i++) {
        if(i != S){
            total += D_res[i];
        }
    }

    printf("%lld\n", total);
    return 0;
}