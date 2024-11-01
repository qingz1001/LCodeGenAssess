#include <stdio.h>
#include <string.h>

#define MAX_N 101
#define MAX_P 10000

int n, p;
int state[MAX_N], threshold[MAX_N];
int graph[MAX_N][MAX_N];
int is_output[MAX_N];

void process_network() {
    int changed = 1;
    while (changed) {
        changed = 0;
        for (int i = 0; i < n; i++) {
            int new_state = 0;
            for (int j = 0; j < n; j++) {
                new_state += graph[j][i] * state[j];
            }
            new_state -= threshold[i];
            if (new_state != state[i]) {
                state[i] = new_state;
                changed = 1;
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &p);
    
    memset(graph, 0, sizeof(graph));
    memset(is_output, 1, sizeof(is_output));
    
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &state[i], &threshold[i]);
    }
    
    for (int i = 0; i < p; i++) {
        int from, to, weight;
        scanf("%d %d %d", &from, &to, &weight);
        from--; to--;
        graph[from][to] = weight;
        is_output[from] = 0;
    }
    
    process_network();
    
    int output_count = 0;
    for (int i = 0; i < n; i++) {
        if (is_output[i] && state[i] > 0) {
            printf("%d %d\n", i + 1, state[i]);
            output_count++;
        }
    }
    
    if (output_count == 0) {
        printf("NULL\n");
    }
    
    return 0;
}