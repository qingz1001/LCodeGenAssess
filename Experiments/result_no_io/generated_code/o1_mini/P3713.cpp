#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// Define the modulo constant
#define MOD 1000000009

// Define maximum grid size
#define MAX_M 30
#define MAX_N 30

// Define hash map node
typedef struct HashNode {
    uint64_t hash;
    long long count;
    struct HashNode* next;
} HashNode;

// Define hash map
#define HASH_MAP_SIZE 1000003
HashNode* hash_map[HASH_MAP_SIZE];

// Function to compute hash index
unsigned int get_hash_index(uint64_t hash) {
    return hash % HASH_MAP_SIZE;
}

// Function to insert or update hash count
void insert_hash(uint64_t hash) {
    unsigned int idx = get_hash_index(hash);
    HashNode* node = hash_map[idx];
    while(node){
        if(node->hash == hash){
            node->count++;
            return;
        }
        node = node->next;
    }
    // Not found, create new
    HashNode* new_node = (HashNode*)malloc(sizeof(HashNode));
    new_node->hash = hash;
    new_node->count = 1;
    new_node->next = hash_map[idx];
    hash_map[idx] = new_node;
}

// Directions for 8-connected movement
int dx[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
int dy[8] = {-1, 0, 1, 1, 1, 0, -1, -1};

// Grid variables
int m, n;
char grid[MAX_M][MAX_N+1];

// To store the sum
long long total = 0;

// Maximum path length
int max_path = 900;

// Function to perform DFS and count terrain sequences
void dfs(int x, int y, uint64_t current_hash, int visited[][MAX_N]) {
    // Insert the current hash into the hash map
    insert_hash(current_hash);
    
    // Iterate over all 8 directions
    for(int dir=0; dir<8; dir++){
        int nx = x + dx[dir];
        int ny = y + dy[dir];
        
        // Check bounds
        if(nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
        
        // Check if already visited
        if(visited[nx][ny]) continue;
        
        // Determine movement constraints will be handled externally
        
        // Mark as visited
        visited[nx][ny] = 1;
        
        // Update hash: simple polynomial rolling hash
        uint64_t new_hash = current_hash * 257 + (uint64_t)grid[nx][ny];
        
        // Continue DFS
        dfs(nx, ny, new_hash, visited);
        
        // Unmark
        visited[nx][ny] = 0;
    }
}

int main(){
    // Read grid size
    scanf("%d %d", &m, &n);
    
    // Read grid
    for(int i=0; i<m; i++){
        scanf("%s", grid[i]);
    }
    
    // Iterate over all possible start positions
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            // Initialize visited array
            int visited[MAX_M][MAX_N];
            memset(visited, 0, sizeof(visited));
            visited[i][j] = 1;
            
            // Initialize hash with first character
            uint64_t initial_hash = (uint64_t)grid[i][j];
            
            // Start DFS
            dfs(i, j, initial_hash, visited);
        }
    }
    
    // Iterate over hash map and sum squares
    for(int i=0; i<HASH_MAP_SIZE; i++){
        HashNode* node = hash_map[i];
        while(node){
            total = (total + (node->count * node->count) % MOD) % MOD;
            node = node->next;
        }
    }
    
    // Print the result
    printf("%lld\n", total);
    
    // Free hash map
    for(int i=0; i<HASH_MAP_SIZE; i++){
        HashNode* node = hash_map[i];
        while(node){
            HashNode* temp = node;
            node = node->next;
            free(temp);
        }
    }
    
    return 0;
}