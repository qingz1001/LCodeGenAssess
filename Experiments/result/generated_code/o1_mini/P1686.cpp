#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 2097152

typedef struct {
    long long key;
    int value;
    char filled;
} HashEntry;

// Initialize hash tables for N, E, S, W
HashEntry hash_N[HASH_SIZE];
HashEntry hash_E[HASH_SIZE];
HashEntry hash_S[HASH_SIZE];
HashEntry hash_W[HASH_SIZE];

// Function to compute hash index
int get_hash(long long key){
    int hash = key % HASH_SIZE;
    if(hash < 0) hash += HASH_SIZE;
    return hash;
}

int main(){
    int n;
    scanf("%d", &n);
    char *steps = (char*)malloc((n+1)*sizeof(char));
    scanf("%s", steps);
    
    // Allocate memory for positions
    int *x = (int*)malloc((n+1)*sizeof(int));
    int *y = (int*)malloc((n+1)*sizeof(int));
    x[0] = 0;
    y[0] = 0;
    for(int j=1; j<=n; j++){
        x[j] = x[j-1];
        y[j] = y[j-1];
        switch(steps[j-1]){
            case 'N': y[j] +=1; break;
            case 'E': x[j] +=1; break;
            case 'S': y[j] -=1; break;
            case 'W': x[j] -=1; break;
        }
    }
    free(steps);
    
    // Initialize minimum shortcut
    int min_len = n+1;
    int min_i = 0;
    int min_j = 0;
    char min_dir = 'N';
    
    for(int j=0; j<=n; j++){
        // N direction
        long long key_N_val = ((long long)x[j] * 3000000LL) + (long long)(y[j] - j);
        int hash_idx = get_hash(key_N_val);
        while(hash_N[hash_idx].filled){
            if(hash_N[hash_idx].key == key_N_val){
                int i = hash_N[hash_idx].value;
                int len = j - i;
                if(len < min_len || (len == min_len && (i < min_i || (i == min_i && j > min_j)))){
                    min_len = len;
                    min_i = i;
                    min_j = j;
                    min_dir = 'N';
                }
                break;
            }
            hash_idx = (hash_idx +1) % HASH_SIZE;
        }
        if(!hash_N[hash_idx].filled){
            hash_N[hash_idx].key = key_N_val;
            hash_N[hash_idx].value = j;
            hash_N[hash_idx].filled = 1;
        }
        
        // E direction
        long long key_E_val = ((long long)y[j] * 3000000LL) + (long long)(x[j] - j);
        hash_idx = get_hash(key_E_val);
        while(hash_E[hash_idx].filled){
            if(hash_E[hash_idx].key == key_E_val){
                int i = hash_E[hash_idx].value;
                int len = j - i;
                if(len < min_len || (len == min_len && (i < min_i || (i == min_i && j > min_j)))){
                    min_len = len;
                    min_i = i;
                    min_j = j;
                    min_dir = 'E';
                }
                break;
            }
            hash_idx = (hash_idx +1) % HASH_SIZE;
        }
        if(!hash_E[hash_idx].filled){
            hash_E[hash_idx].key = key_E_val;
            hash_E[hash_idx].value = j;
            hash_E[hash_idx].filled = 1;
        }
        
        // S direction
        long long key_S_val = ((long long)x[j] * 3000000LL) + (long long)(y[j] + j);
        hash_idx = get_hash(key_S_val);
        while(hash_S[hash_idx].filled){
            if(hash_S[hash_idx].key == key_S_val){
                int i = hash_S[hash_idx].value;
                int len = j - i;
                if(len < min_len || (len == min_len && (i < min_i || (i == min_i && j > min_j)))){
                    min_len = len;
                    min_i = i;
                    min_j = j;
                    min_dir = 'S';
                }
                break;
            }
            hash_idx = (hash_idx +1) % HASH_SIZE;
        }
        if(!hash_S[hash_idx].filled){
            hash_S[hash_idx].key = key_S_val;
            hash_S[hash_idx].value = j;
            hash_S[hash_idx].filled = 1;
        }
        
        // W direction
        long long key_W_val = ((long long)y[j] * 3000000LL) + (long long)(x[j] + j);
        hash_idx = get_hash(key_W_val);
        while(hash_W[hash_idx].filled){
            if(hash_W[hash_idx].key == key_W_val){
                int i = hash_W[hash_idx].value;
                int len = j - i;
                if(len < min_len || (len == min_len && (i < min_i || (i == min_i && j > min_j)))){
                    min_len = len;
                    min_i = i;
                    min_j = j;
                    min_dir = 'W';
                }
                break;
            }
            hash_idx = (hash_idx +1) % HASH_SIZE;
        }
        if(!hash_W[hash_idx].filled){
            hash_W[hash_idx].key = key_W_val;
            hash_W[hash_idx].value = j;
            hash_W[hash_idx].filled = 1;
        }
    }
    
    printf("%d %d %d %c\n", min_len, min_i, min_j, min_dir);
    
    // Free memory
    free(x);
    free(y);
    
    return 0;
}