#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 200001
#define MAX_EDGES 400002
#define MAX_POOL 6000000
#define MOD 786433

typedef struct {
    long long x;
    long long power;
    int next;
} cache_entry;

// Hash table for caching x^x mod MOD
cache_entry hash_table_entries[MAX_POOL];
int hash_table_heads[786433];
int pool_ptr = 0;

// Function to compute a^b mod mod
long long power_func(long long a, long long b, long long mod_val){
    if(a ==0 && b ==0){
        return 0;
    }
    if(b ==0){
        return 1;
    }
    long long result =1;
    a %= mod_val;
    while(b >0){
        if(b & 1){
            result = (result * a) % mod_val;
        }
        a = (a * a) % mod_val;
        b >>=1;
    }
    return result;
}

// Function to get x^x mod MOD with caching
long long get_power(long long x){
    if(x ==0){
        return 0;
    }
    int h = x % MOD;
    int idx = hash_table_heads[h];
    while(idx != -1){
        if(hash_table_entries[idx].x == x){
            return hash_table_entries[idx].power;
        }
        idx = hash_table_entries[idx].next;
    }
    // Not found, compute it
    long long p = power_func(x, x, MOD);
    // Add to hash table
    if(pool_ptr >= MAX_POOL){
        // Should not happen
        return 0;
    }
    hash_table_entries[pool_ptr].x = x;
    hash_table_entries[pool_ptr].power = p;
    hash_table_entries[pool_ptr].next = hash_table_heads[h];
    hash_table_heads[h] = pool_ptr;
    pool_ptr++;
    return p;
}

// Comparator for descending order
int cmp_desc(const void *a, const void *b){
    long long A = *(long long*)a;
    long long B = *(long long*)b;
    if(A > B) return -1;
    if(A < B) return 1;
    return 0;
}

// Adjacency list
int head_adj[MAXN];
int to_adj[MAX_EDGES];
int next_adj_edge[MAX_EDGES];
int edge_count =0;

// Function to add edge to adjacency list
void add_edge(int u, int v){
    to_adj[edge_count] = v;
    next_adj_edge[edge_count] = head_adj[u];
    head_adj[u] = edge_count++;
}

// Queue for BFS
int queue_nodes[MAXN];
int queue_parents[MAXN];
int front_q =0, back_q =0;

// Lists for dynamic programming
long long all_ands[MAX_POOL];
int all_counts_arr[MAX_POOL];
int node_ptrs[MAXN];
int node_sizes_arr[MAXN];
long long a_vals[MAXN];

// Temporary arrays
long long temp_xs[31];
int temp_size;
int unique_size;

// Global pointer for all_ands and all_counts_arr
int global_ptr =0;

// Main function
int main(){
    // Initialize hash table heads to -1
    for(int i=0;i<MOD;i++) hash_table_heads[i] = -1;
    
    int n;
    scanf("%d", &n);
    for(int i=1;i<=n;i++) scanf("%lld", &a_vals[i]);
    for(int i=0;i<n-1;i++){
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }
    
    // Initialize BFS
    int root =1;
    queue_nodes[back_q] = root;
    queue_parents[back_q++] = -1;
    
    unsigned long long sum =0;
    
    while(front_q < back_q){
        int node = queue_nodes[front_q];
        int parent = queue_parents[front_q];
        front_q++;
        
        // Process current node
        if(parent == -1){
            // Only the node itself
            temp_xs[0] = a_vals[node];
            temp_size =1;
        }
        else{
            // AND with parent's list
            temp_size =0;
            for(int i=0;i<node_sizes_arr[parent];i++){
                if(global_ptr + temp_size >= MAX_POOL){
                    // Prevent overflow
                    break;
                }
                temp_xs[temp_size++] = all_ands[node_ptrs[parent] +i] & a_vals[node];
            }
            // Add the node itself
            temp_xs[temp_size++] = a_vals[node];
        }
        
        // Sort temp_xs in descending order
        qsort(temp_xs, temp_size, sizeof(long long), cmp_desc);
        
        // Group and count unique x's
        unique_size =0;
        int start =0;
        while(start < temp_size){
            long long current = temp_xs[start];
            int cnt =1;
            int end = start +1;
            while(end < temp_size && temp_xs[end] == current){
                cnt++;
                end++;
            }
            if(global_ptr >= MAX_POOL){
                // Prevent overflow
                break;
            }
            all_ands[global_ptr] = current;
            all_counts_arr[global_ptr] = cnt;
            unique_size++;
            global_ptr++;
            start = end;
        }
        
        // Assign to current node
        node_ptrs[node] = global_ptr - unique_size;
        node_sizes_arr[node] = unique_size;
        
        // Accumulate to sum
        for(int i = node_ptrs[node]; i < node_ptrs[node] + node_sizes_arr[node]; i++){
            long long x = all_ands[i];
            int cnt = all_counts_arr[i];
            long long powx;
            if(x ==0){
                powx =0;
            }
            else{
                powx = get_power(x);
            }
            sum = (sum + (powx * cnt) % MOD) % MOD;
        }
        
        // Enqueue children
        for(int e = head_adj[node]; e != -1; e = next_adj_edge[e]){
            int neighbor = to_adj[e];
            if(neighbor != parent){
                queue_nodes[back_q] = neighbor;
                queue_parents[back_q++] = node;
            }
        }
    }
    
    printf("%llu\n", sum);
    return 0;
}