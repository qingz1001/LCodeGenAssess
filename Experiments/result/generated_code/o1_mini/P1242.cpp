#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 45
#define PEGS 3
#define HASH_SIZE 1000003
#define QUEUE_SIZE 10000000

typedef struct {
    unsigned long long pegs_bits[PEGS];
} State;

typedef struct {
    State state;
    int parent;
    int move_disk;
    int from;
    int to;
} Node;

typedef struct {
    unsigned long long key1;
    unsigned long long key2;
    int index;
} HashEntry;

Node queue[QUEUE_SIZE];
int front = 0, rear = 0;
HashEntry hash_table_arr[HASH_SIZE];
int hash_count = 0;

// Function to compute hash
unsigned long compute_hash(unsigned long long a, unsigned long long b) {
    return (a ^ b) % HASH_SIZE;
}

// Function to check if state is visited
int is_visited(State *s) {
    unsigned long h = compute_hash(s->pegs_bits[0], s->pegs_bits[1]);
    for(int i = 0; i < HASH_SIZE; i++) {
        unsigned long idx = (h + i) % HASH_SIZE;
        if(hash_table_arr[idx].index == -1){
            return -1;
        }
        if(hash_table_arr[idx].key1 == s->pegs_bits[0] && hash_table_arr[idx].key2 == s->pegs_bits[1]){
            return hash_table_arr[idx].index;
        }
    }
    return -1;
}

// Function to mark state as visited
void mark_visited(State *s, int index) {
    unsigned long h = compute_hash(s->pegs_bits[0], s->pegs_bits[1]);
    for(int i = 0; i < HASH_SIZE; i++) {
        unsigned long idx = (h + i) % HASH_SIZE;
        if(hash_table_arr[idx].index == -1){
            hash_table_arr[idx].key1 = s->pegs_bits[0];
            hash_table_arr[idx].key2 = s->pegs_bits[1];
            hash_table_arr[idx].index = index;
            return;
        }
    }
}

// Function to copy state
void copy_state(State *dest, State *src){
    dest->pegs_bits[0] = src->pegs_bits[0];
    dest->pegs_bits[1] = src->pegs_bits[1];
    dest->pegs_bits[2] = src->pegs_bits[2];
}

// Function to get top disk on a peg
int get_top_disk(State *s, int peg, int n){
    for(int disk = 1; disk <= n; disk++){
        int p;
        if(disk <= 32){
            p = (s->pegs_bits[peg] >> ((disk-1)*2)) & 3;
        }
        else{
            p = (s->pegs_bits[peg] >> ((disk-33)*2)) & 3;
        }
        if(p == peg){
            return disk;
        }
    }
    return -1;
}

// Function to set disk position
void set_disk(State *s, int disk, int peg){
    if(disk <= 32){
        s->pegs_bits[peg] &= ~(3ULL << ((disk-1)*2));
        s->pegs_bits[peg] |= ((unsigned long long)peg << ((disk-1)*2));
    }
    else{
        s->pegs_bits[peg] &= ~(3ULL << ((disk-33)*2));
        s->pegs_bits[peg] |= ((unsigned long long)peg << ((disk-33)*2));
    }
}

int main(){
    int n;
    scanf("%d", &n);
    // Initialize hash table
    for(int i = 0; i < HASH_SIZE; i++) hash_table_arr[i].index = -1;
    // Read initial state
    State initial;
    memset(&initial, 0, sizeof(State));
    for(int peg = 0; peg < PEGS; peg++){
        int count;
        scanf("%d", &count);
        for(int i = 0; i < count; i++){
            int disk;
            scanf("%d", &disk);
            set_disk(&initial, disk, peg);
        }
    }
    // Read target state
    State target;
    memset(&target, 0, sizeof(State));
    for(int peg = 0; peg < PEGS; peg++){
        int count;
        scanf("%d", &count);
        for(int i = 0; i < count; i++){
            int disk;
            scanf("%d", &disk);
            set_disk(&target, disk, peg);
        }
    }
    // Initialize queue
    queue[0].state = initial;
    queue[0].parent = -1;
    queue[0].move_disk = -1;
    queue[0].from = -1;
    mark_visited(&initial, 0);
    rear++;
    // BFS
    while(front < rear){
        Node current = queue[front];
        // Check if target
        if(current.state.pegs_bits[0] == target.pegs_bits[0] &&
           current.state.pegs_bits[1] == target.pegs_bits[1] &&
           current.state.pegs_bits[2] == target.pegs_bits[2]){
            // Reconstruct path
            int path_len = 0;
            int idx = front;
            while(idx != -1){
                path_len++;
                idx = queue[idx].parent;
            }
            char **moves = (char**)malloc(sizeof(char*) * (path_len-1));
            idx = front;
            for(int i = path_len-2; i >=0; i--){
                moves[i] = strdup(queue[idx].move);
                idx = queue[idx].parent;
            }
            for(int i = 0; i < path_len-1; i++) printf("%s\n", moves[i]);
            printf("%d\n", path_len-1);
            return 0;
        }
        // Generate possible moves
        for(int from = 0; from < PEGS; from++){
            // Find top disk on 'from' peg
            int top_disk = get_top_disk(&current.state, from, n);
            if(top_disk == -1) continue;
            for(int to = 0; to < PEGS; to++){
                if(from == to) continue;
                // Check if move is valid
                int target_disk = get_top_disk(&current.state, to, n);
                if(target_disk == -1 || top_disk < target_disk){
                    // Make move
                    State new_state = current.state;
                    set_disk(&new_state, top_disk, to);
                    // Check if visited
                    if(is_visited(&new_state) == -1){
                        // Add to queue
                        if(rear >= QUEUE_SIZE){
                            // Queue overflow
                            exit(0);
                        }
                        queue[rear].state = new_state;
                        queue[rear].parent = front;
                        queue[rear].move_disk = top_disk;
                        queue[rear].from = from;
                        queue[rear].to = to;
                        // Create move string
                        char move_str[30];
                        char peg_from = 'A' + from;
                        char peg_to = 'A' + to;
                        sprintf(move_str, "move %d from %c to %c", top_disk, peg_from, peg_to);
                        strcpy(queue[rear].move, move_str);
                        mark_visited(&new_state, rear);
                        rear++;
                    }
                }
            }
        }
        front++;
    }
    return 0;
}