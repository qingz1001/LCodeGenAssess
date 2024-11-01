#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1000001

typedef struct Node {
    int to;
    struct Node* next;
} Node;

Node* adj[MAXN];
int parent_node[MAXN];
int visited[MAXN];
int path_nodes[MAXN];
int path_length = 0;

// Function to add edge to adjacency list
void add_edge(int a, int b){
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->to = b;
    new_node->next = adj[a];
    adj[a] = new_node;
}

// Queue for BFS
typedef struct Queue {
    int* data;
    int front;
    int rear;
    int size;
} Queue;

Queue* create_queue(int size){
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->data = (int*)malloc(sizeof(int)*size);
    q->front = 0;
    q->rear = 0;
    q->size = size;
    return q;
}

int is_empty(Queue* q){
    return q->front == q->rear;
}

void enqueue(Queue* q, int x){
    q->data[q->rear++] = x;
}

int dequeue(Queue* q){
    return q->data[q->front++];
}

int main(){
    int n, t, m;
    scanf("%d %d %d", &n, &t, &m);
    for(int i=0;i<n-1;i++){
        int a, b;
        scanf("%d %d", &a, &b);
        add_edge(a, b);
        add_edge(b, a);
    }
    
    // BFS from t
    Queue* q = create_queue(n);
    enqueue(q, t);
    visited[t] = 1;
    parent_node[t] = -1;
    while(!is_empty(q)){
        int u = dequeue(q);
        for(Node* ptr = adj[u]; ptr != NULL; ptr = ptr->next){
            int v = ptr->to;
            if(!visited[v]){
                visited[v] = 1;
                parent_node[v] = u;
                enqueue(q, v);
                if(v == m){
                    break;
                }
            }
        }
    }
    
    // Reconstruct path from m to t
    int current = m;
    while(current != -1){
        path_nodes[path_length++] = current;
        current = parent_node[current];
    }
    
    // Mark nodes on path
    int on_path[MAXN];
    memset(on_path, 0, sizeof(on_path));
    for(int i=0;i<path_length;i++) on_path[path_nodes[i]] = 1;
    
    // Count the number of edges not on path
    long long operations = 0;
    for(int i=0;i<path_length;i++){
        int u = path_nodes[i];
        for(Node* ptr = adj[u]; ptr != NULL; ptr = ptr->next){
            int v = ptr->to;
            if(!on_path[v]){
                operations++;
            }
        }
    }
    
    printf("%lld\n", operations);
    
    // Free memory
    for(int i=1;i<=n;i++){
        Node* ptr = adj[i];
        while(ptr){
            Node* temp = ptr;
            ptr = ptr->next;
            free(temp);
        }
    }
    free(q->data);
    free(q);
    
    return 0;
}