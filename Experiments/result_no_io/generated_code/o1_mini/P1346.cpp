#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 101
#define MAXK 10000

typedef struct {
    int to;
} Edge;

typedef struct {
    Edge edges[MAXK];
    int cnt;
    int default_edge;
} Node;

typedef struct {
    int data[MAXK];
    int front;
    int rear;
} Deque;

void initDeque(Deque* dq){
    dq->front = 0;
    dq->rear = 0;
}

int isEmpty(Deque* dq){
    return dq->front == dq->rear;
}

void pushFront(Deque* dq, int val){
    dq->front--;
    dq->data[dq->front] = val;
}

void pushBack(Deque* dq, int val){
    dq->data[dq->rear++] = val;
}

int popFront(Deque* dq){
    return dq->data[dq->front++];
}

int main(){
    int N, A, B;
    scanf("%d %d %d", &N, &A, &B);
    Node graph[MAXN];
    for(int i=1;i<=N;i++){
        int Ki;
        scanf("%d", &Ki);
        graph[i].cnt = Ki;
        for(int j=0; j<Ki; j++){
            int to;
            scanf("%d", &to);
            graph[i].edges[j].to = to;
        }
        if(Ki > 0)
            graph[i].default_edge = graph[i].edges[0].to;
        else
            graph[i].default_edge = -1;
    }
    int dist[MAXN];
    for(int i=1;i<=N;i++) dist[i] = -1;
    Deque dq;
    initDeque(&dq);
    pushBack(&dq, A);
    dist[A] = 0;
    while(!isEmpty(&dq)){
        int u = popFront(&dq);
        if(u == B) break;
        for(int i=0;i<graph[u].cnt;i++){
            int v = graph[u].edges[i].to;
            int cost = (i == 0) ? 0 : 1;
            if(dist[v]==-1 || dist[v] > dist[u] + cost){
                dist[v] = dist[u] + cost;
                if(cost == 0)
                    pushFront(&dq, v);
                else
                    pushBack(&dq, v);
            }
        }
    }
    printf("%d\n", dist[B]);
    return 0;
}