#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100

typedef struct {
    int state;
    int threshold;
} Neuron;

typedef struct {
    int from;
    int to;
    int weight;
} Edge;

int main() {
    int n, p;
    scanf("%d %d", &n, &p);

    Neuron neurons[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &neurons[i].state, &neurons[i].threshold);
        if (i > 0) {
            neurons[i].state = 0;
        }
    }

    Edge edges[p];
    for (int i = 0; i < p; i++) {
        scanf("%d %d %d", &edges[i].from, &edges[i].to, &edges[i].weight);
    }

    int changed = 1;
    while (changed) {
        changed = 0;
        for (int i = 0; i < p; i++) {
            int from = edges[i].from - 1;
            int to = edges[i].to - 1;
            int weight = edges[i].weight;
            if (neurons[from].state > neurons[from].threshold && neurons[to].state <= 0) {
                neurons[to].state += weight * neurons[from].state;
                if (neurons[to].state > neurons[to].threshold) {
                    changed = 1;
                }
            }
        }
    }

    int output_count = 0;
    for (int i = 0; i < n; i++) {
        if (neurons[i].state > neurons[i].threshold) {
            printf("%d %d\n", i + 1, neurons[i].state);
            output_count++;
        }
    }

    if (output_count == 0) {
        printf("NULL\n");
    }

    return 0;
}