#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef unsigned long long ull;

// Queue implementation
typedef struct {
    int *data;
    int front;
    int rear;
    int size;
    int capacity;
} Queue;

// Initialize queue
Queue* initQueue(int capacity) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->data = (int*)malloc(sizeof(int) * capacity);
    q->front = 0;
    q->rear = 0;
    q->size = 0;
    q->capacity = capacity;
    return q;
}

// Enqueue
void enqueue(Queue* q, int val) {
    if (q->size == q->capacity) {
        q->capacity *= 2;
        q->data = (int*)realloc(q->data, sizeof(int) * q->capacity);
    }
    q->data[q->rear++] = val;
    if (q->rear == q->capacity) q->rear = 0;
    q->size++;
}

// Dequeue
int dequeue(Queue* q) {
    int val = q->data[q->front++];
    if (q->front == q->capacity) q->front = 0;
    q->size--;
    return val;
}

// Check if queue is empty
int isEmpty(Queue* q) {
    return q->size == 0;
}

// Monster structure
typedef struct {
    ull S;
    ull K;
    int R;
    int *A;
} Monster;

int main(){
    int N;
    scanf("%d", &N);
    
    // Allocate monsters
    Monster* monsters = (Monster*)malloc(sizeof(Monster) * (N+1));
    
    // To store all A_i temporarily
    int total_R = 0;
    int* temp_A = (int*)malloc(sizeof(int) * 1000000); // sum R_i <=1e6
    int temp_ptr = 0;
    
    // Read monsters
    for(int i=1;i<=N;i++){
        ull S_i, K_i;
        int R_i;
        scanf("%llu %llu %d", &S_i, &K_i, &R_i);
        monsters[i].S = S_i;
        monsters[i].K = K_i;
        monsters[i].R = R_i;
        if(R_i > 0){
            monsters[i].A = &temp_A[temp_ptr];
            for(int j=0;j<R_i;j++){
                scanf("%d", &temp_A[temp_ptr++]);
            }
        }
        else{
            monsters[i].A = NULL;
        }
        total_R += R_i;
    }
    
    // Build reverse adjacency list
    // First, count rev_count
    ull* rev_count = (ull*)calloc(N+1, sizeof(ull));
    for(int i=1;i<=N;i++){
        for(int j=0;j<monsters[i].R;j++){
            int a = monsters[i].A[j];
            rev_count[a]++;
        }
    }
    
    // Allocate rev_start and populate
    ull* rev_start = (ull*)malloc(sizeof(ull) * (N+1));
    ull* current_rev = (ull*)malloc(sizeof(ull) * (N+1));
    memset(current_rev, 0, sizeof(ull)*(N+1));
    rev_start[1] = 0;
    for(int i=1;i<=N;i++){
        rev_start[i] = (i==1) ? 0 : rev_start[i-1] + rev_count[i-1];
    }
    
    // Allocate rev array
    int* rev = (int*)malloc(sizeof(int) * total_R);
    
    // Temporary array to keep track of current position
    ull* temp_pos = (ull*)malloc(sizeof(ull) * (N+1));
    memset(temp_pos, 0, sizeof(ull)*(N+1));
    
    // Populate rev array
    for(int i=1;i<=N;i++){
        for(int j=0;j<monsters[i].R;j++){
            int a = monsters[i].A[j];
            rev[rev_start[a] + temp_pos[a]++] = i;
        }
    }
    
    free(temp_pos);
    
    // Initialize C_i and total_sum
    ull* C = (ull*)malloc(sizeof(ull)*(N+1));
    ull* total_sum = (ull*)malloc(sizeof(ull)*(N+1));
    for(int i=1;i<=N;i++) {
        C[i] = monsters[i].K;
    }
    for(int i=1;i<=N;i++){
        ull sum = 0;
        for(int j=0;j<monsters[i].R;j++){
            int a = monsters[i].A[j];
            sum += C[a];
        }
        total_sum[i] = sum;
    }
    
    // Initialize queue
    Queue* q = initQueue(1024);
    // Initial update
    for(int i=1;i<=N;i++){
        ull option = monsters[i].S + total_sum[i];
        if(option < C[i]){
            C[i] = option;
            enqueue(q, i);
        }
    }
    
    // Process queue
    while(!isEmpty(q)){
        int i = dequeue(q);
        // For each monster that depends on i
        ull C_i = C[i];
        for(ull idx = rev_start[i]; idx < rev_start[i] + rev_count[i]; idx++){
            int j = rev[idx];
            ull old_total = total_sum[j];
            total_sum[j] = total_sum[j] - monsters[i].K + C_i;
            ull option = monsters[j].S + total_sum[j];
            if(option < C[j]){
                C[j] = option;
                enqueue(q, j);
            }
        }
    }
    
    // The answer is C[1]
    printf("%llu\n", C[1]);
    
    // Free memory
    free(monsters);
    free(temp_A);
    free(rev_count);
    free(rev_start);
    free(rev);
    free(C);
    free(total_sum);
    free(q->data);
    free(q);
    
    return 0;
}