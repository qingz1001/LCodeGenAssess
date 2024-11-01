#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NODES 500005
#define MAX_PATTERNS 100005
#define MAX_OUTPUT 500005
#define ALPHABET 4

typedef struct {
    int children[ALPHABET];
    int fail;
    int output_start;
    int output_end;
} Node;

Node nodes[MAX_NODES];
int output_list[MAX_OUTPUT];
int output_ptr = 0;
int v_i[MAX_PATTERNS];
int counts[MAX_PATTERNS];
int n, m;
char s_buffer[500005];
char S_buffer[500005];
int queue_nodes[MAX_NODES];
int head, tail;

// Comparator for descending order
int cmp_desc(const void *a, const void *b){
    int x = *(int*)a;
    int y = *(int*)b;
    if(y > x) return 1;
    else if(y < x) return -1;
    else return 0;
}

int main(){
    // Initialize root
    memset(nodes, -1, sizeof(nodes));
    nodes[0].fail = 0;
    nodes[0].output_start = 0;
    nodes[0].output_end = 0;
    
    // Read n and m
    scanf("%d %d", &n, &m);
    
    // Insert patterns into trie
    for(int i=0; i<n; i++){
        scanf("%s %d", s_buffer, &v_i[i]);
        int current = 0;
        int len = strlen(s_buffer);
        for(int j=0; j<len; j++){
            int c = s_buffer[j] - 'a';
            if(nodes[current].children[c] == -1){
                nodes[current].children[c] = ++output_ptr;
                memset(&nodes[output_ptr], -1, sizeof(Node));
                nodes[output_ptr].fail = 0;
                nodes[output_ptr].output_start = nodes[output_ptr].output_end = 0;
            }
            current = nodes[current].children[c];
        }
        output_list[output_ptr++] = i;
        nodes[current].output_end++;
    }
    
    // Build fail links
    head = 0;
    tail = 0;
    queue_nodes[tail++] = 0;
    while(head < tail){
        int current = queue_nodes[head++];
        for(int c=0; c<ALPHABET; c++){
            if(nodes[current].children[c] != -1){
                int child = nodes[current].children[c];
                if(current == 0){
                    nodes[child].fail = 0;
                }
                else{
                    int f = nodes[current].fail;
                    while(f != 0 && nodes[f].children[c] == -1){
                        f = nodes[f].fail;
                    }
                    if(nodes[f].children[c] != -1){
                        nodes[child].fail = nodes[f].children[c];
                    }
                    else{
                        nodes[child].fail = 0;
                    }
                }
                // Merge output
                nodes[child].output_start = output_ptr;
                for(int o = nodes[nodes[child].fail].output_start; o < nodes[nodes[child].fail].output_start + nodes[nodes[child].fail].output_end; o++){
                    output_list[output_ptr++] = output_list[o];
                }
                nodes[child].output_end += nodes[nodes[child].fail].output_end;
                queue_nodes[tail++] = child;
            }
            else{
                if(current == 0){
                    nodes[current].children[c] = 0;
                }
                else{
                    nodes[current].children[c] = nodes[nodes[current].fail].children[c];
                }
            }
        }
    }
    
    // Temporary list for active patterns
    int active_list[500];
    
    for(int q=0; q<m; q++){
        scanf("%s %d", S_buffer, &n); // Reusing n as k
        int k = n;
        // Read k
        // Process S
        int current = 0;
        int len = strlen(S_buffer);
        int active_count = 0;
        for(int j=0; j<len; j++){
            int c = S_buffer[j] - 'a';
            current = nodes[current].children[c];
            for(int o = nodes[current].output_start; o < nodes[current].output_start + nodes[current].output_end; o++){
                int pattern = output_list[o];
                if(counts[pattern] == 0){
                    active_list[active_count++] = pattern;
                }
                counts[pattern]++;
            }
        }
        // Collect w_i
        int w_list[500];
        int w_size = 0;
        for(int i=0; i<active_count; i++){
            int pattern = active_list[i];
            w_list[w_size++] = counts[pattern] * v_i[pattern];
        }
        // Sort descending
        if(w_size > 0){
            qsort(w_list, w_size, sizeof(int), cmp_desc);
        }
        // Find k-th
        if(k <= w_size){
            printf("%d\n", w_list[k-1]);
        }
        else{
            printf("0\n");
        }
        // Reset counts
        for(int i=0; i<active_count; i++){
            counts[active_list[i]] = 0;
        }
    }
    return 0;
}