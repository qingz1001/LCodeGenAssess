#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_M 1000
#define MAX_DIGITS 10000

typedef struct {
    int front, rear;
    int data[MAX_M];
} Queue;

void initQueue(Queue *q) {
    q->front = 0;
    q->rear = 0;
}

int isEmpty(Queue *q) {
    return q->front == q->rear;
}

void enqueue(Queue *q, int x) {
    q->data[q->rear++] = x;
}

int dequeue(Queue *q) {
    return q->data[q->front++];
}

int main(){
    int k, m;
    scanf("%d %d", &k, &m);
    if(m ==0){
        printf("0");
        return 0;
    }
    int parent[MAX_M];
    int digit_store[MAX_M];
    for(int i=0;i<m;i++){ parent[i]=-1; digit_store[i]=-1; }
    Queue q;
    initQueue(&q);
    for(int d=1; d<k; d++){
        int rem = d % m;
        if(parent[rem]==-1){
            parent[rem] = -2;
            digit_store[rem] = d;
            enqueue(&q, rem);
            if(rem ==0){
                // Reconstruct
                char number[MAX_DIGITS];
                int pos=0;
                number[pos++] = '0';
                number[pos]='\0';
                for(int i=pos-1;i>=0;i--) {}
                number[pos]='\0';
                // Since starting digit is d
                number[pos++] = '0' + d;
                number[pos]='\0';
                printf("%d", d);
                return 0;
            }
        }
    }
    while(!isEmpty(&q)){
        int current = dequeue(&q);
        for(int d=0; d<k; d++){
            int new_rem = (current *10 + d) % m;
            if(parent[new_rem]==-1){
                parent[new_rem] = current;
                digit_store[new_rem] = d;
                enqueue(&q, new_rem);
                if(new_rem ==0){
                    // Reconstruct
                    char number[MAX_DIGITS];
                    int pos=0;
                    int rem = new_rem;
                    while(parent[rem]!=-2){
                        number[pos++] = '0' + digit_store[rem];
                        rem = parent[rem];
                    }
                    number[pos++] = '0' + digit_store[rem];
                    for(int i=pos-1;i>=0;i--) printf("%c", number[i]);
                    return 0;
                }
            }
        }
    }
    return 0;
}