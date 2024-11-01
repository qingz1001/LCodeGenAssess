#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 1001
#define MAXM 200001
#define EPS 1e-6

typedef struct {
    int to;
    int S;
    int next;
} Edge;

Edge edgeList[MAXM];
int headList[MAXN];
int currentEdge = 0;

typedef struct {
    int data[MAXM];
    int front;
    int rear;
} Queue;

void enqueue(Queue *q, int x){
    q->data[q->rear++] = x;
}

int dequeue(Queue *q){
    return q->data[q->front++];
}

int isEmpty(Queue *q){
    return q->front == q->rear;
}

int main(){
    int N, M;
    if(scanf("%d %d", &N, &M)!=2){
        return 0;
    }
    for(int i=1;i<=N;i++) headList[i] = -1;
    for(int i=0;i<M;i++){
        int u, v, S;
        if(scanf("%d %d %d", &u, &v, &S)!=3){
            return 0;
        }
        edgeList[currentEdge].to = v;
        edgeList[currentEdge].S = S;
        edgeList[currentEdge].next = headList[u];
        headList[u] = currentEdge++;
        edgeList[currentEdge].to = u;
        edgeList[currentEdge].S = S;
        edgeList[currentEdge].next = headList[v];
        headList[v] = currentEdge++;
    }
    double val[MAXN];
    int visited[MAXN];
    for(int i=1;i<=N;i++) visited[i] = 0;
    Queue q;
    q.front = q.rear =0;
    for(int i=1;i<=N;i++){
        if(!visited[i]){
            val[i] = 0.0;
            visited[i] = 1;
            enqueue(&q, i);
            while(!isEmpty(&q)){
                int u = dequeue(&q);
                for(int k = headList[u]; k != -1; k = edgeList[k].next){
                    int v = edgeList[k].to;
                    int S = edgeList[k].S;
                    if(!visited[v]){
                        val[v] = (double)S - val[u];
                        visited[v] = 1;
                        enqueue(&q, v);
                    }
                    else{
                        double expected = (double)S - val[u];
                        if(fabs(val[v] - expected) > EPS){
                            printf("IMPOSSIBLE\n");
                            return 0;
                        }
                    }
                }
            }
        }
    }
    for(int i=1;i<=N;i++){
        printf("%.2lf\n", val[i]);
    }
    return 0;
}