#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int a, b, c;
    int steps;
} State;

typedef struct Node {
    State state;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
} Queue;

typedef struct VisitedNode {
    int64_t key;
    struct VisitedNode* next;
} VisitedNode;

#define HASH_SIZE 1000003

VisitedNode* hashTable[HASH_SIZE];

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int64_t get_key(int a, int b, int c){
    return ((int64_t)(a) << 40) | ((int64_t)(b) << 20) | (int64_t)(c);
}

int is_visited(int a, int b, int c){
    int64_t key = get_key(a, b, c);
    int idx = key % HASH_SIZE;
    VisitedNode* node = hashTable[idx];
    while(node){
        if(node->key == key) return 1;
        node = node->next;
    }
    return 0;
}

void add_visited(int a, int b, int c){
    int64_t key = get_key(a, b, c);
    int idx = key % HASH_SIZE;
    VisitedNode* node = (VisitedNode*)malloc(sizeof(VisitedNode));
    node->key = key;
    node->next = hashTable[idx];
    hashTable[idx] = node;
}

void enqueue(Queue* q, State s){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->state = s;
    newNode->next = NULL;
    if(q->rear){
        q->rear->next = newNode;
        q->rear = newNode;
    }
    else{
        q->front = q->rear = newNode;
    }
}

int dequeue(Queue* q, State* s){
    if(q->front == NULL) return 0;
    Node* temp = q->front;
    *s = temp->state;
    q->front = q->front->next;
    if(q->front == NULL) q->rear = NULL;
    free(temp);
    return 1;
}

int main(){
    int a, b, c;
    int x, y, z;
    scanf("%d %d %d", &a, &b, &c);
    scanf("%d %d %d", &x, &y, &z);
    int initial[3] = {a, b, c};
    int target[3] = {x, y, z};
    qsort(initial, 3, sizeof(int), compare);
    qsort(target, 3, sizeof(int), compare);
    Queue q = {NULL, NULL};
    State start = {initial[0], initial[1], initial[2], 0};
    enqueue(&q, start);
    add_visited(start.a, start.b, start.c);
    while(q.front){
        State current;
        dequeue(&q, &current);
        if(current.a == target[0] && current.b == target[1] && current.c == target[2]){
            printf("YES\n%d\n", current.steps);
            return 0;
        }
        // Generate all possible moves
        int pos[3] = {current.a, current.b, current.c};
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++) if(j != i){
                // Jump i over j
                int new_pos = 2*pos[j] - pos[i];
                // Check if new_pos is not occupied
                if(new_pos != pos[0] && new_pos != pos[1] && new_pos != pos[2]){
                    int new_p[3];
                    new_p[0] = new_pos;
                    new_p[1] = pos[(i+1)%3];
                    new_p[2] = pos[(i+2)%3];
                    qsort(new_p, 3, sizeof(int), compare);
                    if(!is_visited(new_p[0], new_p[1], new_p[2])){
                        State next = {new_p[0], new_p[1], new_p[2], current.steps +1};
                        enqueue(&q, next);
                        add_visited(new_p[0], new_p[1], new_p[2]);
                    }
                }
            }
        }
    }
    printf("NO\n");
    return 0;
}