#include <stdio.h>
#include <string.h>

#define MAX_N 100
#define MAX_P 10000

int n, p;
int state[MAX_N + 1], threshold[MAX_N + 1];
int weight[MAX_N + 1][MAX_N + 1];
int output[MAX_N + 1];

void calculate_states() {
    int new_state[MAX_N + 1];
    int changed = 1;
    
    while (changed) {
        changed = 0;
        memset(new_state, 0, sizeof(new_state));
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (weight[j][i] != 0) {
                    new_state[i] += weight[j][i] * state[j];
                }
            }
            new_state[i] -= threshold[i];
            
            if (new_state[i] != state[i]) {
                changed = 1;
            }
        }
        
        memcpy(state, new_state, sizeof(state));
    }
}

int main() {
    scanf("%d %d", &n, &p);
    
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &state[i], &threshold[i]);
    }
    
    for (int i = 0; i < p; i++) {
        int from, to, w;
        scanf("%d %d %d", &from, &to, &w);
        weight[from][to] = w;
    }
    
    calculate_states();
    
    int output_count = 0;
    for (int i = 1; i <= n; i++) {
        if (state[i] > 0) {
            output[output_count++] = i;
        }
    }
    
    if (output_count == 0) {
        printf("NULL\n");
    } else {
        for (int i = 0; i < output_count; i++) {
            printf("%d %d\n", output[i], state[output[i]]);
        }
    }
    
    return 0;
}