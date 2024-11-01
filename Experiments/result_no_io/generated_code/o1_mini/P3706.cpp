#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_NODES 100000
#define MAX_PATTERNS 300
#define MAX_M 300
#define MAX_QUEUE MAX_NODES
#define EPSILON 1e-12

typedef struct {
    int children[2];
    int fail;
    int output; // -1 if no output, else pattern index
} Node;

Node trie[MAX_NODES];
int node_count = 1; // Start with root at 0

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    char patterns[MAX_PATTERNS][301];
    for(int i=0;i<n;i++) {
        scanf("%s", patterns[i]);
    }

    // Initialize trie
    for(int i=0;i<MAX_NODES;i++){
        trie[i].children[0] = -1;
        trie[i].children[1] = -1;
        trie[i].fail = 0;
        trie[i].output = -1;
    }

    // Insert patterns
    for(int i=0;i<n;i++){
        int current = 0;
        for(int j=0;j<m;j++){
            int c = patterns[i][j] == 'H' ? 0 : 1;
            if(trie[current].children[c]==-1){
                trie[current].children[c] = node_count;
                node_count++;
            }
            current = trie[current].children[c];
        }
        if(trie[current].output == -1 || trie[current].output > i){
            trie[current].output = i;
        }
    }

    // Build fail links using BFS
    int queue[MAX_QUEUE];
    int front = 0, rear = 0;

    // Initialize fail links for depth 1 nodes
    for(int c=0;c<2;c++){
        if(trie[0].children[c] != -1){
            trie[trie[0].children[c]].fail = 0;
            queue[rear++] = trie[0].children[c];
        }
        else{
            trie[0].children[c] = 0;
        }
    }

    // BFS
    while(front < rear){
        int current = queue[front++];
        for(int c=0;c<2;c++){
            if(trie[current].children[c] != -1){
                int child = trie[current].children[c];
                int fail = trie[current].fail;
                while(trie[fail].children[c]==-1 && fail !=0){
                    fail = trie[fail].fail;
                }
                if(trie[fail].children[c]!=-1){
                    fail = trie[fail].children[c];
                }
                trie[child].fail = fail;
                if(trie[fail].output != -1){
                    if(trie[child].output == -1 || trie[child].output > trie[fail].output){
                        trie[child].output = trie[fail].output;
                    }
                }
                queue[rear++] = child;
            }
            else{
                trie[current].children[c] = trie[trie[current].fail].children[c];
            }
        }
    }

    // Identify absorbing states and map to pattern indices
    int total_states = node_count;
    int is_absorbing[MAX_NODES];
    int absorb_id[MAX_NODES];
    for(int i=0;i<total_states;i++){
        if(trie[i].output != -1){
            is_absorbing[i] = 1;
            absorb_id[i] = trie[i].output;
        }
        else{
            is_absorbing[i] = 0;
            absorb_id[i] = -1;
        }
    }

    // Initialize probability arrays
    double P[MAX_PATTERNS];
    for(int i=0;i<n;i++) P[i] = 0.0;

    double current_flow[MAX_NODES];
    double next_flow_arr[MAX_NODES];
    memset(current_flow, 0, sizeof(current_flow));
    memset(next_flow_arr, 0, sizeof(next_flow_arr));
    current_flow[0] = 1.0;

    // To keep track of active states
    int active_current[MAX_NODES];
    int active_count_current = 0;
    active_current[active_count_current++] = 0;

    int active_next[MAX_NODES];
    int active_count_next = 0;

    while(active_count_current >0){
        active_count_next =0;
        // Process all active states
        for(int ai=0; ai < active_count_current; ai++){
            int s = active_current[ai];
            double flow = current_flow[s];
            if(flow < EPSILON) continue;
            if(is_absorbing[s]) continue;
            // For 'H' and 'T'
            for(int c=0;c<2;c++){
                int next_s = trie[s].children[c];
                if(is_absorbing[next_s]){
                    P[absorb_id[next_s]] += 0.5 * flow;
                }
                else{
                    if(next_flow_arr[next_s] < EPSILON){
                        active_next[active_count_next++] = next_s;
                    }
                    next_flow_arr[next_s] += 0.5 * flow;
                }
            }
            current_flow[s] = 0.0;
        }
        // Prepare for next iteration
        for(int ai=0; ai < active_count_next; ai++){
            int s = active_next[ai];
            current_flow[s] += next_flow_arr[s];
            next_flow_arr[s] = 0.0;
        }
        // Swap active lists
        memcpy(active_current, active_next, sizeof(int)*active_count_next);
        active_count_current = active_count_next;
    }

    // Print results
    for(int i=0;i<n;i++){
        printf("%.10lf\n", P[i]);
    }

    return 0;
}