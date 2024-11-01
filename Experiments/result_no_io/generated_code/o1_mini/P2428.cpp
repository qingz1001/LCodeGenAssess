#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_N 1001
#define MAX_M 100000
#define EPS 1e-6

typedef struct Edge {
    int to;
    int c;
    struct Edge* next;
} Edge;

Edge* adj[MAX_N];
double debt_val[MAX_N];
int assigned[MAX_N];

typedef struct Queue {
    int data[MAX_N];
    int front;
    int back;
} Queue;

void enqueue(Queue* q, int x) {
    q->data[q->back++] = x;
}

int dequeue(Queue* q) {
    return q->data[q->front++];
}

int main(){
    int N,M;
    scanf("%d %d", &N, &M);
    
    for(int i=0;i<M;i++){
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        Edge* e1 = (Edge*)malloc(sizeof(Edge));
        e1->to = b;
        e1->c = c;
        e1->next = adj[a];
        adj[a] = e1;
        
        Edge* e2 = (Edge*)malloc(sizeof(Edge));
        e2->to = a;
        e2->c = c;
        e2->next = adj[b];
        adj[b] = e2;
    }
    
    memset(assigned, 0, sizeof(assigned));
    memset(debt_val, 0, sizeof(debt_val));
    
    Queue q;
    q.front = q.back = 0;
    
    for(int i=1;i<=N;i++){
        if(!assigned[i]){
            debt_val[i] = 0.0;
            assigned[i] = 1;
            enqueue(&q, i);
            while(q.front < q.back){
                int current = dequeue(&q);
                Edge* e = adj[current];
                while(e){
                    int neighbor = e->to;
                    double expected = (double)e->c - debt_val[current];
                    if(!assigned[neighbor]){
                        debt_val[neighbor] = expected;
                        assigned[neighbor] = 1;
                        enqueue(&q, neighbor);
                    }
                    else{
                        if(fabs(debt_val[neighbor] - expected) > EPS){
                            printf("IMPOSSIBLE\n");
                            return 0;
                        }
                    }
                    e = e->next;
                }
            }
        }
    }
    
    // Verify all equations
    for(int i=1;i<=N;i++){
        Edge* e = adj[i];
        while(e){
            if(i < e->to){
                double sum = debt_val[i] + debt_val[e->to];
                if(fabs(sum - (double)e->c) > EPS){
                    printf("IMPOSSIBLE\n");
                    return 0;
                }
            }
            e = e->next;
        }
    }
    
    for(int i=1;i<=N;i++){
        printf("%.2lf\n", debt_val[i]);
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