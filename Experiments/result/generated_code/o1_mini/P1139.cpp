#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 15
#define MAX_STATE 1000000
#define MAX_MOVES 256

typedef struct {
    char A[MAX_N + 1];
    char B[MAX_N + 1];
    char C[MAX_N + 1];
    char D[MAX_N + 1];
    char moves[MAX_MOVES][7];
    int move_count;
} State;

typedef struct {
    State *states;
    int front;
    int rear;
    int size;
} Queue;

// Initialize the queue
Queue* initQueue(int max_size) {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->states = (State*)malloc(sizeof(State) * max_size);
    q->front = 0;
    q->rear = 0;
    q->size = max_size;
    return q;
}

// Check if queue is empty
int isEmpty(Queue *q) {
    return q->front == q->rear;
}

// Enqueue a state
int enqueue(Queue *q, State *s) {
    if (q->rear >= q->size) return 0;
    q->states[q->rear++] = *s;
    return 1;
}

// Dequeue a state
int dequeue(Queue *q, State *s) {
    if (isEmpty(q)) return 0;
    *s = q->states[q->front++];
    return 1;
}

// Check if two strings are equal
int str_equal(const char *s1, const char *s2) {
    return strcmp(s1, s2) == 0;
}

// Generate initial A
void generate_initial_A(char *A, int n) {
    for(int i=0;i<n;i++) {
        A[i] = 'a' + i;
    }
    A[n] = '\0';
}

int main(){
    int n;
    char desired[MAX_N +1];
    scanf("%d", &n);
    scanf("%s", desired);
    
    // Initialize BFS
    Queue *q = initQueue(MAX_STATE);
    State initial;
    generate_initial_A(initial.A, n);
    initial.B[0] = '\0';
    initial.C[0] = '\0';
    initial.D[0] = '\0';
    initial.move_count = 0;
    enqueue(q, &initial);
    
    // Visited state storage
    // Using a simplistic visited mechanism due to time constraints
    // Not optimized for large n
    char visited[MAX_STATE][4*(MAX_N+1)];
    int visited_count = 0;
    
    while(!isEmpty(q)){
        State current;
        dequeue(q, &current);
        
        // Check if D matches desired
        if(str_equal(current.D, desired)){
            for(int i=0;i<current.move_count;i++){
                printf("%s\n", current.moves[i]);
            }
            return 0;
        }
        
        // Possible moves: A->B, A->C, A->D, B->D, C->D
        // Move A->B
        if(current.A[0] != '\0'){
            State next = current;
            char h = current.A[0];
            // Shift A
            memmove(next.A, current.A +1, strlen(current.A));
            // Push to B
            int lenB = strlen(current.B);
            next.B[lenB] = h;
            next.B[lenB+1] = '\0';
            // Record move
            strcpy(next.moves[next.move_count], "");
            sprintf(next.moves[next.move_count], "%c A B", h);
            next.move_count++;
            enqueue(q, &next);
        }
        
        // Move A->C
        if(current.A[0] != '\0'){
            State next = current;
            char h = current.A[0];
            // Shift A
            memmove(next.A, current.A +1, strlen(current.A));
            // Push to C
            int lenC = strlen(current.C);
            next.C[lenC] = h;
            next.C[lenC+1] = '\0';
            // Record move
            strcpy(next.moves[next.move_count], "");
            sprintf(next.moves[next.move_count], "%c A C", h);
            next.move_count++;
            enqueue(q, &next);
        }
        
        // Move A->D
        if(current.A[0] != '\0'){
            char next_char = desired[strlen(current.D)];
            if(current.A[0] == next_char){
                State next = current;
                char h = current.A[0];
                // Shift A
                memmove(next.A, current.A +1, strlen(current.A));
                // Push to D
                int lenD = strlen(current.D);
                next.D[lenD] = h;
                next.D[lenD+1] = '\0';
                // Record move
                strcpy(next.moves[next.move_count], "");
                sprintf(next.moves[next.move_count], "%c A D", h);
                next.move_count++;
                enqueue(q, &next);
            }
        }
        
        // Move B->D
        if(current.B[0] != '\0'){
            char next_char = desired[strlen(current.D)];
            char h = current.B[strlen(current.B)-1];
            if(h == next_char){
                State next = current;
                // Pop from B
                next.B[strlen(next.B)-1] = '\0';
                // Push to D
                int lenD = strlen(current.D);
                next.D[lenD] = h;
                next.D[lenD+1] = '\0';
                // Record move
                strcpy(next.moves[next.move_count], "");
                sprintf(next.moves[next.move_count], "%c B D", h);
                next.move_count++;
                enqueue(q, &next);
            }
        }
        
        // Move C->D
        if(current.C[0] != '\0'){
            char next_char = desired[strlen(current.D)];
            char h = current.C[strlen(current.C)-1];
            if(h == next_char){
                State next = current;
                // Pop from C
                next.C[strlen(next.C)-1] = '\0';
                // Push to D
                int lenD = strlen(current.D);
                next.D[lenD] = h;
                next.D[lenD+1] = '\0';
                // Record move
                strcpy(next.moves[next.move_count], "");
                sprintf(next.moves[next.move_count], "%c C D", h);
                next.move_count++;
                enqueue(q, &next);
            }
        }
    }
    
    // If no solution found
    printf("NO");
    return 0;
}