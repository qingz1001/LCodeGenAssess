#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAXN 100005
typedef long long ll;

typedef struct Edge {
    int to;
    ll len;
    struct Edge* next;
} Edge;

Edge* graph[MAXN];
ll dist1[MAXN];
ll dist2[MAXN];
int N;

// Queue for BFS
typedef struct Queue {
    int data[MAXN];
    int front, rear;
} Queue;

void enqueue(Queue* q, int x){
    q->data[q->rear++] = x;
}

int dequeue(Queue* q){
    return q->data[q->front++];
}

int is_empty(Queue* q){
    return q->front == q->rear;
}

void add_edge(int u, int v, ll l){
    Edge* e = (Edge*)malloc(sizeof(Edge));
    e->to = v;
    e->len = l;
    e->next = graph[u];
    graph[u] = e;
}

void bfs(int start, ll* distance){
    memset(distance, -1, sizeof(ll)* (N+1));
    Queue q;
    q.front = q.rear =0;
    enqueue(&q, start);
    distance[start] =0;
    while(!is_empty(&q)){
        int u = dequeue(&q);
        Edge* e = graph[u];
        while(e){
            int v = e->to;
            if(distance[v]==-1){
                distance[v] = distance[u] + e->len;
                enqueue(&q, v);
            }
            e = e->next;
        }
    }
}

int main(){
    scanf("%d", &N);
    for(int i=0;i<N;i++){
        int A,B;
        ll L;
        scanf("%d %d %lld", &A, &B, &L);
        add_edge(A, B, L);
        add_edge(B, A, L);
    }
    // First BFS to find one end
    bfs(1, dist1);
    int far =1;
    for(int i=1;i<=N;i++) if(dist1[i]>dist1[far]) far =i;
    // Second BFS to find diameter
    bfs(far, dist1);
    int far2 = far;
    for(int i=1;i<=N;i++) if(dist1[i]>dist1[far2]) far2 =i;
    ll diameter = dist1[far2];
    double res = (double)diameter /2.0;
    // Print with one decimal
    printf("%.1lf\n", res);
    return 0;
}