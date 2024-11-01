#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 201

typedef struct {
    int data[MAX];
    int front;
    int rear;
} Queue;

void init_queue(Queue *q) {
    q->front = 0;
    q->rear = 0;
}

int is_empty(Queue *q) {
    return q->front == q->rear;
}

void enqueue(Queue *q, int val) {
    if(q->rear < MAX){
        q->data[q->rear++] = val;
    }
}

int dequeue(Queue *q) {
    if(!is_empty(q)){
        return q->data[q->front++];
    }
    return -1;
}

int main(){
    int N, A, B;
    scanf("%d %d %d", &N, &A, &B);
    int K[MAX];
    for(int i=1;i<=N;i++) scanf("%d", &K[i]);
    int visited[MAX];
    memset(visited, -1, sizeof(visited));
    Queue q;
    init_queue(&q);
    enqueue(&q, A);
    visited[A] = 0;
    while(!is_empty(&q)){
        int current = dequeue(&q);
        if(current == B){
            printf("%d", visited[current]);
            return 0;
        }
        // Up
        if(K[current] > 0){
            int up = current + K[current];
            if(up <= N && visited[up]==-1){
                visited[up] = visited[current]+1;
                enqueue(&q, up);
            }
            int down = current - K[current];
            if(down >=1 && visited[down]==-1){
                visited[down] = visited[current]+1;
                enqueue(&q, down);
            }
        }
    }
    printf("-1");
    return 0;
}