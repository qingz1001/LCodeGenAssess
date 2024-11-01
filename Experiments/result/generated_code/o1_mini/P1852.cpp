#include <stdio.h>
#include <stdlib.h>

// Define the size of the hash table
#define HASH_SIZE 1000003

typedef struct state_node {
    int a, b, c;
    struct state_node *next;
} state_node;

// Queue implementation
typedef struct {
    int a, b, c;
    int steps;
} queue_item;

#define MAX_QUEUE 1000000
queue_item queue_array[MAX_QUEUE];
int head = 0, tail = 0;

// Hash table
state_node* hash_table[HASH_SIZE] = {NULL};

// Function to sort three integers
void sort_three(int *a, int *b, int *c) {
    int tmp;
    if (*a > *b) { tmp = *a; *a = *b; *b = tmp; }
    if (*a > *c) { tmp = *a; *a = *c; *c = tmp; }
    if (*b > *c) { tmp = *b; *b = *c; *c = tmp; }
}

// Function to compute hash
unsigned int compute_hash(int a, int b, int c) {
    unsigned long long key = (unsigned long long)(a + 1000000001LL) * 4000000003ULL 
                             + (unsigned long long)(b + 1000000001LL) * 2000000011ULL 
                             + (unsigned long long)(c + 1000000001LL);
    return key % HASH_SIZE;
}

// Function to check if state is visited
int is_visited(int a, int b, int c) {
    unsigned int hash = compute_hash(a, b, c);
    state_node *node = hash_table[hash];
    while (node) {
        if (node->a == a && node->b == b && node->c == c)
            return 1;
        node = node->next;
    }
    return 0;
}

// Function to mark state as visited
void mark_visited(int a, int b, int c) {
    unsigned int hash = compute_hash(a, b, c);
    state_node *new_node = (state_node*)malloc(sizeof(state_node));
    new_node->a = a;
    new_node->b = b;
    new_node->c = c;
    new_node->next = hash_table[hash];
    hash_table[hash] = new_node;
}

// Function to enqueue a new state
int enqueue(int a, int b, int c, int steps) {
    if (tail >= MAX_QUEUE)
        return 0;
    queue_array[tail].a = a;
    queue_array[tail].b = b;
    queue_array[tail].c = c;
    queue_array[tail].steps = steps;
    tail++;
    return 1;
}

int main(){
    int a, b, c;
    int x, y, z;
    
    // Read initial positions
    scanf("%d %d %d", &a, &b, &c);
    sort_three(&a, &b, &c);
    
    // Read target positions
    scanf("%d %d %d", &x, &y, &z);
    sort_three(&x, &y, &z);
    
    // If initial is target
    if(a == x && b == y && c == z){
        printf("YES\n0");
        return 0;
    }
    
    // Initialize BFS
    enqueue(a, b, c, 0);
    mark_visited(a, b, c);
    
    // BFS loop
    while(head < tail){
        int current_a = queue_array[head].a;
        int current_b = queue_array[head].b;
        int current_c = queue_array[head].c;
        int current_steps = queue_array[head].steps;
        head++;
        
        // Generate all possible moves
        int pieces[3] = {current_a, current_b, current_c};
        for(int i=0;i<3;i++){ // Choose middle piece
            for(int j=0;j<3;j++){ // Choose piece to jump
                if(j == i) continue;
                int new_pos = 2 * pieces[i] - pieces[j];
                // Check if new_pos is already occupied
                if(new_pos == pieces[0] || new_pos == pieces[1] || new_pos == pieces[2]){
                    continue;
                }
                // Create new state
                int new_a = pieces[i];
                int new_b = pieces[j] < new_pos ? pieces[j] : new_pos;
                int new_c = pieces[j] < new_pos ? new_pos : pieces[j];
                sort_three(&new_a, &new_b, &new_c);
                
                // Check if visited
                if(!is_visited(new_a, new_b, new_c)){
                    // Check if target
                    if(new_a == x && new_b == y && new_c == z){
                        printf("YES\n%d", current_steps + 1);
                        return 0;
                    }
                    // Enqueue new state
                    enqueue(new_a, new_b, new_c, current_steps + 1);
                    mark_visited(new_a, new_b, new_c);
                    if(tail >= MAX_QUEUE){
                        break;
                    }
                }
            }
            if(tail >= MAX_QUEUE){
                break;
            }
        }
    }
    
    // If not found
    printf("NO");
    return 0;
}