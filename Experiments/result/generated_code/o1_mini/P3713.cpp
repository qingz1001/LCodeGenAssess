#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 1000000009
#define MAX_M 30
#define MAX_N 30
#define MAX_PATH 900
#define HASH_SIZE 10000019

typedef struct Entry {
    unsigned long long hash;
    long long count;
    struct Entry* next;
} Entry;

unsigned long long base = 911382629;

// Simple hash function for strings using polynomial rolling hash
unsigned long long compute_hash(char* str, int len) {
    unsigned long long h = 0;
    for(int i=0;i<len;i++) {
        h = h * base + (unsigned char)str[i];
    }
    return h;
}

// Hash table with chaining
Entry* hash_table[HASH_SIZE];

void insert_hash(unsigned long long hash) {
    unsigned long long key = hash % HASH_SIZE;
    Entry* entry = hash_table[key];
    while(entry) {
        if(entry->hash == hash){
            entry->count +=1;
            return;
        }
        entry = entry->next;
    }
    // Not found, create new
    Entry* new_entry = (Entry*)malloc(sizeof(Entry));
    new_entry->hash = hash;
    new_entry->count =1;
    new_entry->next = hash_table[key];
    hash_table[key] = new_entry;
}

int m, n;
char grid[MAX_M][MAX_N];
int visited[MAX_M][MAX_N];
char path[MAX_PATH];
int path_len;

// Directions: 8-connected
int dx[8] = {-1,-1,-1,0,1,1,1,0};
int dy[8] = {-1,0,1,1,1,0,-1,-1};

void dfs(int x, int y, char* t, int tx, int ty) {
    // Append current terrain
    path[path_len++] = grid[x][y];
    // Compute hash for current path
    unsigned long long current_hash = compute_hash(path, path_len);
    insert_hash(current_hash);
    
    for(int dir=0; dir<8; dir++) {
        int nx = x + dx[dir];
        int ny = y + dy[dir];
        if(nx <0 || nx >=m || ny <0 || ny >=n) continue;
        if(visited[nx][ny]) continue;
        // Movement constraint: not moving away in x and y from t
        if(tx >= x) {
            if(nx < x) continue;
        }
        else {
            if(nx > x) continue;
        }
        if(ty >= y) {
            if(ny < y) continue;
        }
        else {
            if(ny > y) continue;
        }
        // Mark and recurse
        visited[nx][ny] =1;
        dfs(nx, ny, t, tx, ty);
        visited[nx][ny] =0;
    }
    path_len--;
}

int main(){
    scanf("%d %d", &m, &n);
    for(int i=0;i<m;i++) {
        scanf("%s", grid[i]);
    }
    long long total =0;
    // Iterate over all possible start and end positions
    for(int sx=0;sx<m;sx++) {
        for(int sy=0;sy<n;sy++) {
            for(int tx=0;tx<m;tx++) {
                for(int ty=0;ty<n;ty++) {
                    if(sx == tx && sy == ty) continue;
                    // Initialize visited
                    memset(visited, 0, sizeof(visited));
                    visited[sx][sy] =1;
                    path_len=0;
                    dfs(sx, sy, grid[tx][ty] ? grid[tx][ty] : grid[sx][sy], tx, ty);
                }
            }
        }
    }
    // Iterate over hash table to compute sum of k^2
    for(int i=0;i<HASH_SIZE;i++) {
        Entry* entry = hash_table[i];
        while(entry){
            total = (total + (entry->count * entry->count) % MOD) % MOD;
            entry = entry->next;
        }
    }
    printf("%lld\n", total);
    // Free memory
    for(int i=0;i<HASH_SIZE;i++) {
        Entry* entry = hash_table[i];
        while(entry){
            Entry* tmp = entry;
            entry = entry->next;
            free(tmp);
        }
    }
    return 0;
}