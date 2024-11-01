#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define maximum sizes
#define MAX_NODES 500005
#define MAX_PATTERNS 100005
#define MAX_MATCHES 5000000
#define ALPHABET 4

// Structure for Aho-Corasick nodes
typedef struct Node {
    int next[ALPHABET];
    int fail;
    int *output;
    int output_size;
    int output_capacity;
} Node;

// Initialize nodes
Node nodes_pool[MAX_NODES];
int node_count = 1; // 0 is root

// Function to create a new node
int create_node() {
    if (node_count >= MAX_NODES) {
        // Handle overflow
        return 0;
    }
    nodes_pool[node_count].fail = 0;
    nodes_pool[node_count].output = NULL;
    nodes_pool[node_count].output_size = 0;
    nodes_pool[node_count].output_capacity = 0;
    for(int i=0;i<ALPHABET;i++) nodes_pool[node_count].next[i] = -1;
    return node_count++;
}

// Function to add a pattern to the trie
int add_pattern(char *s, int pattern_id) {
    int current = 0;
    for(int i=0; s[i]; i++) {
        int c = s[i] - 'a';
        if(nodes_pool[current].next[c]==-1){
            nodes_pool[current].next[c] = create_node();
        }
        current = nodes_pool[current].next[c];
    }
    // Add pattern id to the output of the current node
    if(nodes_pool[current].output_capacity == 0){
        nodes_pool[current].output_capacity = 2;
        nodes_pool[current].output = (int*)malloc(sizeof(int) * nodes_pool[current].output_capacity);
    }
    else if(nodes_pool[current].output_size == nodes_pool[current].output_capacity){
        nodes_pool[current].output_capacity *= 2;
        nodes_pool[current].output = (int*)realloc(nodes_pool[current].output, sizeof(int) * nodes_pool[current].output_capacity);
    }
    nodes_pool[current].output[nodes_pool[current].output_size++] = pattern_id;
    return current;
}

int main(){
    // Fast IO
    char buffer[500005];
    int n, m;
    scanf("%d %d", &n, &m);
    
    // Arrays to store pattern info
    char **patterns = (char**)malloc(sizeof(char*) * n);
    int *v = (int*)malloc(sizeof(int) * n);
    int *pattern_end_node = (int*)malloc(sizeof(int) * n);
    
    // Initialize root
    for(int i=0;i<ALPHABET;i++) nodes_pool[0].next[i]=-1;
    
    // Read patterns
    for(int i=0;i<n;i++){
        char s[21];
        scanf("%s %d", s, &v[i]);
        int node = add_pattern(s, i);
        pattern_end_node[i] = node;
    }
    
    // Build failure links using BFS
    int *queue = (int*)malloc(sizeof(int) * node_count);
    int head = 0, tail = 0;
    // Initialize queue with depth 1 nodes
    for(int c=0; c<ALPHABET; c++){
        if(nodes_pool[0].next[c] != -1){
            nodes_pool[nodes_pool[0].next[c]].fail = 0;
            queue[tail++] = nodes_pool[0].next[c];
        }
        else{
            nodes_pool[0].next[c] = 0;
        }
    }
    // BFS
    while(head < tail){
        int current = queue[head++];
        for(int c=0; c<ALPHABET; c++){
            if(nodes_pool[current].next[c] != -1){
                int child = nodes_pool[current].next[c];
                int fail = nodes_pool[current].fail;
                while(nodes_pool[fail].next[c] == -1 && fail != 0){
                    fail = nodes_pool[fail].fail;
                }
                if(nodes_pool[fail].next[c] != -1){
                    fail = nodes_pool[fail].next[c];
                }
                nodes_pool[child].fail = fail;
                // Merge output
                if(nodes_pool[fail].output_size > 0){
                    for(int i=0;i<nodes_pool[fail].output_size;i++){
                        // Add to child's output
                        if(nodes_pool[child].output_capacity == 0){
                            nodes_pool[child].output_capacity = 2;
                            nodes_pool[child].output = (int*)malloc(sizeof(int) * nodes_pool[child].output_capacity);
                        }
                        else if(nodes_pool[child].output_size == nodes_pool[child].output_capacity){
                            nodes_pool[child].output_capacity *=2;
                            nodes_pool[child].output = (int*)realloc(nodes_pool[child].output, sizeof(int) * nodes_pool[child].output_capacity);
                        }
                        nodes_pool[child].output[nodes_pool[child].output_size++] = nodes_pool[fail].output[i];
                    }
                }
                queue[tail++] = child;
            }
            else{
                nodes_pool[current].next[c] = nodes_pool[nodes_pool[current].fail].next[c];
            }
        }
    }
    free(queue);
    
    // Prepare for queries
    // Initialize counts
    int *last_query = (int*)malloc(sizeof(int) * n);
    int *current_cnt = (int*)malloc(sizeof(int) * n);
    memset(last_query, -1, sizeof(int) * n);
    
    // Allocate a list to store w_i per query
    int *w_list = (int*)malloc(sizeof(int) * n);
    
    // Process each query
    for(int q=0; q<m; q++){
        char S[500005];
        int k;
        scanf("%s %d", S, &k);
        int current_node = 0;
        int matched = 0;
        // List to store unique matched pattern indices
        int matched_patterns[1000];
        int matched_size = 0;
        // Traverse S
        for(int i=0; S[i]; i++){
            int c = S[i] - 'a';
            while(nodes_pool[current_node].next[c] == -1 && current_node != 0){
                current_node = nodes_pool[current_node].fail;
            }
            if(nodes_pool[current_node].next[c] != -1){
                current_node = nodes_pool[current_node].next[c];
            }
            // Collect outputs
            if(nodes_pool[current_node].output_size >0){
                for(int j=0; j<nodes_pool[current_node].output_size; j++){
                    int pat = nodes_pool[current_node].output[j];
                    if(last_query[pat] != q){
                        last_query[pat] = q;
                        current_cnt[pat] = 1;
                        matched_patterns[matched_size++] = pat;
                    }
                    else{
                        current_cnt[pat]++;
                    }
                }
            }
        }
        // Collect w_i
        int w_size = 0;
        for(int i=0; i<matched_size; i++){
            int pat = matched_patterns[i];
            w_list[w_size++] = current_cnt[pat] * v[pat];
        }
        // Find k-th largest
        if(w_size < k){
            printf("0\n");
        }
        else{
            // Use quickselect (nth_element equivalent)
            // Implemented as a selection algorithm
            int left = 0, right = w_size -1;
            int target = k-1;
            while(left < right){
                // Partition
                int pivot = w_list[right];
                int p = left;
                for(int i=left; i<right; i++) if(w_list[i] > pivot){
                    int tmp = w_list[i];
                    w_list[i] = w_list[p];
                    w_list[p++] = tmp;
                }
                int tmp = w_list[p];
                w_list[p] = w_list[right];
                w_list[right] = tmp;
                if(p == target) break;
                if(p > target) right = p -1;
                else left = p +1;
            }
            printf("%d\n", w_list[target]);
        }
    }
    
    // Free allocated memory
    for(int i=0;i<node_count;i++) if(nodes_pool[i].output != NULL) free(nodes_pool[i].output);
    free(patterns);
    free(v);
    free(pattern_end_node);
    free(last_query);
    free(current_cnt);
    free(w_list);
    
    return 0;
}