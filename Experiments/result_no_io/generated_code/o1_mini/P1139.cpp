#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 15
#define MAX_MOVES 100
#define HASH_SIZE 1000003

typedef struct {
    int n;
    char desired[MAX_N + 1];
} Input;

typedef struct Move {
    char train;
    char from;
    char to;
} Move;

typedef struct State {
    int posA;
    int posB;
    int posC;
    int posD;
    int next;
    int maskA[MAX_N];
    int stackB[MAX_N];
    int topB;
    int stackC[MAX_N];
    int topC;
    Move path[MAX_MOVES];
    int moveCount;
} State;

typedef struct QueueNode {
    State state;
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode* front;
    QueueNode* rear;
} Queue;

unsigned long hash_state(State* s, int n) {
    unsigned long hash = s->next;
    for(int i=0;i<n;i++) {
        hash = hash * 4 + s->maskA[i];
    }
    for(int i=0;i<s->topB;i++) {
        hash = hash * 4 + s->stackB[i];
    }
    for(int i=0;i<s->topC;i++) {
        hash = hash * 4 + s->stackC[i];
    }
    return hash % HASH_SIZE;
}

int visited_flags[HASH_SIZE];

int enqueue(Queue* q, State* s) {
    QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
    if(!node) return 0;
    node->state = *s;
    node->next = NULL;
    if(q->rear) q->rear->next = node;
    else q->front = node;
    q->rear = node;
    return 1;
}

int dequeue(Queue* q, State* s) {
    if(!q->front) return 0;
    QueueNode* node = q->front;
    *s = node->state;
    q->front = node->next;
    if(!q->front) q->rear = NULL;
    free(node);
    return 1;
}

int main(){
    Input input;
    scanf("%d %s", &input.n, input.desired);
    // Initialize initial state
    State start;
    start.posA = 0;
    start.posB = 0;
    start.posC = 0;
    start.posD = 0;
    start.next = 0;
    for(int i=0;i<input.n;i++) start.maskA[i] = 0; // 0 for A
    start.topB = 0;
    start.topC = 0;
    start.moveCount = 0;
    
    // Initialize Queue
    Queue q;
    q.front = q.rear = NULL;
    enqueue(&q, &start);
    // Mark visited
    unsigned long h = hash_state(&start, input.n);
    visited_flags[h] = 1;
    
    // BFS
    while(dequeue(&q, &start)){
        if(start.next == input.n){
            // Print path
            for(int i=0;i<start.moveCount;i++) {
                printf("%c,%c,%c\n", start.path[i].train, start.path[i].from, start.path[i].to);
            }
            return 0;
        }
        // Possible moves:
        // 1. Move from A
        if(start.posA < input.n){
            char train = 'a' + start.maskA[start.posA];
            // Move to B
            State nextState = start;
            nextState.path[nextState.moveCount].train = train;
            nextState.path[nextState.moveCount].from = 'A';
            nextState.path[nextState.moveCount].to = 'B';
            nextState.moveCount++;
            nextState.stackB[nextState.topB++] = start.maskA[start.posA];
            nextState.maskA[start.posA] = 1; // B
            nextState.posA++;
            h = hash_state(&nextState, input.n);
            if(!visited_flags[h]){
                visited_flags[h] = 1;
                enqueue(&q, &nextState);
            }
            // Move to C
            nextState = start;
            nextState.path[nextState.moveCount].train = train;
            nextState.path[nextState.moveCount].from = 'A';
            nextState.path[nextState.moveCount].to = 'C';
            nextState.moveCount++;
            nextState.stackC[nextState.topC++] = start.maskA[start.posA];
            nextState.maskA[start.posA] = 2; // C
            nextState.posA++;
            h = hash_state(&nextState, input.n);
            if(!visited_flags[h]){
                visited_flags[h] = 1;
                enqueue(&q, &nextState);
            }
            // Move to D if matches
            if(train == input.desired[start.next]){
                nextState = start;
                nextState.path[nextState.moveCount].train = train;
                nextState.path[nextState.moveCount].from = 'A';
                nextState.path[nextState.moveCount].to = 'D';
                nextState.moveCount++;
                nextState.maskA[start.posA] = 3; // D
                nextState.posA++;
                nextState.next++;
                h = hash_state(&nextState, input.n);
                if(!visited_flags[h]){
                    visited_flags[h] = 1;
                    enqueue(&q, &nextState);
                }
            }
        }
        // 2. Move from B
        if(start.topB > 0){
            int top = start.stackB[start.topB-1];
            char train = 'a' + top;
            if(train == input.desired[start.next]){
                State nextState = start;
                nextState.path[nextState.moveCount].train = train;
                nextState.path[nextState.moveCount].from = 'B';
                nextState.path[nextState.moveCount].to = 'D';
                nextState.moveCount++;
                nextState.topB--;
                nextState.maskA[top] = 3; // D
                nextState.next++;
                h = hash_state(&nextState, input.n);
                if(!visited_flags[h]){
                    visited_flags[h] = 1;
                    enqueue(&q, &nextState);
                }
            }
        }
        // 3. Move from C
        if(start.topC > 0){
            int top = start.stackC[start.topC-1];
            char train = 'a' + top;
            if(train == input.desired[start.next]){
                State nextState = start;
                nextState.path[nextState.moveCount].train = train;
                nextState.path[nextState.moveCount].from = 'C';
                nextState.path[nextState.moveCount].to = 'D';
                nextState.moveCount++;
                nextState.topC--;
                nextState.maskA[top] = 3; // D
                nextState.next++;
                h = hash_state(&nextState, input.n);
                if(!visited_flags[h]){
                    visited_flags[h] = 1;
                    enqueue(&q, &nextState);
                }
            }
        }
    }
    printf("NO");
    return 0;
}