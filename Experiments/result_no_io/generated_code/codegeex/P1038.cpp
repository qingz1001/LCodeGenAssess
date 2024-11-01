#include <stdio.h>
#include <stdlib.h>

#define MAX_NEURONS 100

typedef struct {
    int from;
    int to;
    int weight;
} Edge;

int n, p;
int initial_state[MAX_NEURONS];
int threshold[MAX_NEURONS];
Edge edges[MAX_NEURONS * MAX_NEURONS];
int num_edges[MAX_NEURONS];
int final_state[MAX_NEURONS];

void read_input() {
    scanf("%d %d", &n, &p);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &initial_state[i], &threshold[i]);
    }
    for (int i = 0; i < p; i++) {
        int from, to, weight;
        scanf("%d %d %d", &from, &to, &weight);
        edges[i].from = from - 1;
        edges[i].to = to - 1;
        edges[i].weight = weight;
        num_edges[to - 1]++;
    }
}

void simulate_network() {
    int current_state[MAX_NEURONS];
    for (int i = 0; i < n; i++) {
        current_state[i] = initial_state[i];
    }

    while (1) {
        int changed = 0;
        for (int i = 0; i < n; i++) {
            if (current_state[i] > 0) {
                int outgoing = current_state[i];
                for (int j = 0; j < num_edges[i]; j++) {
                    int next = edges[i * MAX_NEURONS + j].to;
                    current_state[next] += edges[i * MAX_NEURONS + j].weight * outgoing;
                    changed = 1;
                }
            }
        }
        if (!changed) {
            break;
        }
    }

    for (int i = 0; i < n; i++) {
        final_state[i] = current_state[i] - threshold[i];
    }
}

void print_output() {
    int has_positive = 0;
    for (int i = 0; i < n; i++) {
        if (final_state[i] > 0) {
            has_positive = 1;
            printf("%d %d\n", i + 1, final_state[i]);
        }
    }
    if (!has_positive) {
        printf("NULL\n");
    }
}

int main() {
    read_input();
    simulate_network();
    print_output();
    return 0;
}