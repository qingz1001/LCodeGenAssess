#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 101
#define INF 1000000

typedef struct Edge {
    int to;
    int cost;
    struct Edge* next;
} Edge;

typedef struct {
    int data[MAXN*MAXN];
    int front;
    int rear;
} Deque;

void initDeque(Deque* dq) {
    dq->front = 0;
    dq->rear = 0;
}

int isEmpty(Deque* dq) {
    return dq->front == dq->rear;
}

void pushFront(Deque* dq, int val) {
    if(dq->front == 0){
        // Handle underflow if needed
    }
    dq->front--;
    dq->data[dq->front] = val;
}

void pushBack(Deque* dq, int val) {
    dq->data[dq->rear++] = val;
}

int popFront(Deque* dq) {
    return dq->data[dq->front++];
}

int main(){
    int N, A, B;
    scanf("%d %d %d", &N, &A, &B);
    
    Edge* adj[MAXN];
    for(int i=1;i<=N;i++) adj[i] = NULL;
    
    for(int i=1;i<=N;i++){
        int Ki;
        scanf("%d", &Ki);
        if(Ki ==0) continue;
        int first;
        scanf("%d", &first);
        // Add default edge with cost 0
        Edge* e = (Edge*)malloc(sizeof(Edge));
        e->to = first;
        e->cost = 0;
        e->next = adj[i];
        adj[i] = e;
        for(int j=1;j<Ki;j++){
            int dest;
            scanf("%d", &dest);
            Edge* e2 = (Edge*)malloc(sizeof(Edge));
            e2->to = dest;
            e2->cost = 1;
            e2->next = adj[i];
            adj[i] = e2;
        }
    }
    
    int dist[MAXN];
    for(int i=1;i<=N;i++) dist[i] = INF;
    dist[A] = 0;
    
    Deque dq;
    initDeque(&dq);
    pushBack(&dq, A);
    
    while(!isEmpty(&dq)){
        int u = popFront(&dq);
        for(Edge* e = adj[u]; e != NULL; e = e->next){
            if(dist[e->to] > dist[u] + e->cost){
                dist[e->to] = dist[u] + e->cost;
                if(e->cost == 0){
                    pushFront(&dq, e->to);
                }
                else{
                    pushBack(&dq, e->to);
                }
            }
        }
    }
    
    if(dist[B] != INF){
        printf("%d", dist[B]);
    }
    else{
        printf("-1");
    }
    
    // Free memory
    for(int i=1;i<=N;i++){
        Edge* e = adj[i];
        while(e){
            Edge* tmp = e;
            e = e->next;
            free(tmp);
        }
    }
    
    return 0;
}