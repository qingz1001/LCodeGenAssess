#include <stdio.h>
#include <string.h>

#define MAXN 20
#define HASH_SIZE 1000003

typedef struct {
    unsigned long long key1;
    unsigned long long key2;
    int result;
} HashEntry;

HashEntry hash_table[HASH_SIZE];
int hash_used_table[HASH_SIZE] = {0};
int N;
unsigned char initial_edges[MAXN];

// Function to encode state part 1
unsigned long long encode_state1(int pos, unsigned char *edges, int n){
    unsigned long long key = pos;
    for(int i=0; i<n; i++){
        key = key * 31 + edges[i];
    }
    return key;
}

// Function to encode state part 2
unsigned long long encode_state2(int pos, unsigned char *edges, int n){
    unsigned long long key = pos;
    for(int i=0; i<n; i++){
        key = key * 37 + edges[i];
    }
    return key;
}

// Function to get hash index
int get_hash_index(unsigned long long key1, unsigned long long key2){
    return (key1 + key2) % HASH_SIZE;
}

// Recursive function to determine if current player can win
int can_win(int pos, unsigned char edges[]){
    unsigned long long key1 = encode_state1(pos, edges, N);
    unsigned long long key2 = encode_state2(pos, edges, N);
    int hash_idx = get_hash_index(key1, key2);

    // Linear probing to find the state
    while(hash_used_table[hash_idx]){
        if(hash_table[hash_idx].key1 == key1 && hash_table[hash_idx].key2 == key2){
            return hash_table[hash_idx].result;
        }
        hash_idx = (hash_idx + 1) % HASH_SIZE;
    }

    // Mark this state as visited
    hash_used_table[hash_idx] = 1;

    // Determine left and right edges
    int left_edge = (pos + N - 1) % N;
    int right_edge = pos;

    // If both edges are zero, current player loses
    if(edges[left_edge] == 0 && edges[right_edge] == 0){
        hash_table[hash_idx].key1 = key1;
        hash_table[hash_idx].key2 = key2;
        hash_table[hash_idx].result = 0;
        return 0;
    }

    // Try all possible moves on the left edge
    if(edges[left_edge] > 0){
        for(int new_val = 0; new_val < edges[left_edge]; new_val++){
            unsigned char new_edges[MAXN];
            memcpy(new_edges, edges, N);
            new_edges[left_edge] = new_val;
            int new_pos = (pos + N -1) % N;
            if(!can_win(new_pos, new_edges)){
                hash_table[hash_idx].key1 = key1;
                hash_table[hash_idx].key2 = key2;
                hash_table[hash_idx].result = 1;
                return 1;
            }
        }
    }

    // Try all possible moves on the right edge
    if(edges[right_edge] > 0){
        for(int new_val = 0; new_val < edges[right_edge]; new_val++){
            unsigned char new_edges[MAXN];
            memcpy(new_edges, edges, N);
            new_edges[right_edge] = new_val;
            int new_pos = (pos + 1) % N;
            if(!can_win(new_pos, new_edges)){
                hash_table[hash_idx].key1 = key1;
                hash_table[hash_idx].key2 = key2;
                hash_table[hash_idx].result = 1;
                return 1;
            }
        }
    }

    // If no winning move is found, current player loses
    hash_table[hash_idx].key1 = key1;
    hash_table[hash_idx].key2 = key2;
    hash_table[hash_idx].result = 0;
    return 0;
}

int main(){
    scanf("%d", &N);
    for(int i=0; i<N; i++){
        scanf("%hhu", &initial_edges[i]);
    }
    if(can_win(0, initial_edges)){
        printf("YES\n");
    }
    else{
        printf("NO\n");
    }
    return 0;
}