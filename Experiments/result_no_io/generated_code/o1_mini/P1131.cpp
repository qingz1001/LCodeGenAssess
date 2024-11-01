#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 500001
#define MAXM 1000001
typedef long long ll;

// Edge structure
typedef struct {
    int to;
    int t;
    int next;
} Edge;

// Queue for BFS
typedef struct {
    int *data;
    int front;
    int rear;
    int size;
} Queue;

// Initialize queue
Queue* init_queue(int size){
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->data = (int*)malloc(sizeof(int)*(size+1));
    q->front = 0;
    q->rear = 0;
    q->size = size;
    return q;
}

// Enqueue
void enqueue(Queue* q, int x){
    q->data[q->rear++] = x;
}

// Dequeue
int dequeue(Queue* q){
    return q->data[q->front++];
}

// Check if empty
int is_empty(Queue* q){
    return q->front == q->rear;
}

// Free queue
void free_queue(Queue* q){
    free(q->data);
    free(q);
}

Edge edges[MAXM];
int head_list[MAXN];
int edge_cnt = 0;
int degree_cnt[MAXN];
ll D_dist[MAXN];
int terminal[MAXN];
ll x_required[MAXN];
ll max_x[MAXN];
ll total = 0;

// Stack for DFS
typedef struct {
    int u;
    int parent;
    int child_idx;
} Frame;

int main(){
    int N, S;
    scanf("%d", &N);
    scanf("%d", &S);
    // Initialize head_list
    memset(head_list, -1, sizeof(head_list));
    // Read edges
    for(int i=0;i<N-1;i++){
        int a, b, t;
        scanf("%d %d %d", &a, &b, &t);
        edges[edge_cnt].to = b;
        edges[edge_cnt].t = t;
        edges[edge_cnt].next = head_list[a];
        head_list[a] = edge_cnt++;
        edges[edge_cnt].to = a;
        edges[edge_cnt].t = t;
        edges[edge_cnt].next = head_list[b];
        head_list[b] = edge_cnt++;
        degree_cnt[a]++;
        degree_cnt[b]++;
    }
    // Identify terminal nodes
    if(N ==1){
        terminal[S] =1;
    }
    else{
        for(int i=1;i<=N;i++){
            if(i == S){
                if(degree_cnt[i]==0){
                    terminal[i]=1;
                }
            }
            else{
                if(degree_cnt[i]==1){
                    terminal[i]=1;
                }
            }
        }
    }
    // BFS to compute D_dist
    Queue* q = init_queue(N);
    memset(D_dist, -1, sizeof(D_dist));
    enqueue(q, S);
    D_dist[S] = 0;
    while(!is_empty(q)){
        int u = dequeue(q);
        for(int e = head_list[u]; e != -1; e = edges[e].next){
            int v = edges[e].to;
            if(D_dist[v]==-1){
                D_dist[v] = D_dist[u] + edges[e].t;
                enqueue(q, v);
            }
        }
    }
    free_queue(q);
    // Find D_max
    ll D_max = 0;
    for(int i=1;i<=N;i++) if(terminal[i]){
        if(D_dist[i] > D_max){
            D_max = D_dist[i];
        }
    }
    // Set x_required for terminal nodes
    memset(x_required, 0, sizeof(x_required));
    for(int i=1;i<=N;i++) if(terminal[i]){
        x_required[i] = D_max - D_dist[i];
    }
    // Iterative DFS post-order to compute max_x
    Frame* stack = (Frame*)malloc(sizeof(Frame)*N);
    int top =0;
    stack[top].u = S;
    stack[top].parent = -1;
    stack[top].child_idx = head_list[S];
    top++;
    memset(max_x, 0, sizeof(max_x));
    while(top >0){
        Frame current = stack[top-1];
        if(current.child_idx == -1){
            // Process node
            top--;
            if(terminal[current.u]){
                max_x[current.u] = x_required[current.u];
            }
            for(int e = head_list[current.u]; e != -1; e = edges[e].next){
                int v = edges[e].to;
                if(v != current.parent){
                    if(max_x[v] > max_x[current.u]){
                        max_x[current.u] = max_x[v];
                    }
                }
            }
            if(current.parent != -1){
                // Add to total
                total += max_x[current.u];
                // Update parent's max_x
                if(max_x[current.u] + edges[current.child_idx ^1].t > max_x[current.parent]){
                    max_x[current.parent] = max_x[current.u] + edges[current.child_idx ^1].t;
                }
            }
        }
        else{
            // Push child
            int e = current.child_idx;
            int v = edges[e].to;
            if(v != current.parent){
                stack[top].u = v;
                stack[top].parent = current.u;
                stack[top].child_idx = head_list[v];
                top++;
            }
            // Update child_idx
            stack[top-1].child_idx = edges[e].next;
        }
    }
    printf("%lld\n", total);
    free(stack);
    return 0;
}