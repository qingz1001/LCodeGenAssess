#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100

int n, p;
int neurons[MAX_N + 1][2]; // neurons[i][0] 是初始状态，neurons[i][1] 是阈值
int edges[MAX_N + 1][MAX_N + 1]; // 边的权值

void calculate_neuron(int neuron_index) {
    int sum = 0;
    for (int j = 1; j <= n; j++) {
        if (edges[j][neuron_index] != 0) {
            sum += edges[j][neuron_index] * neurons[j][0];
        }
    }
    neurons[neuron_index][0] = sum - neurons[neuron_index][1];
}

int main() {
    scanf("%d %d", &n, &p);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &neurons[i][0], &neurons[i][1]);
    }
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            edges[i][j] = 0;
        }
    }
    for (int i = 0; i < p; i++) {
        int a, b, w;
        scanf("%d %d %d", &a, &b, &w);
        edges[a][b] = w;
    }

    int flag = 0;
    do {
        flag = 0;
        for (int i = 1; i <= n; i++) {
            if (neurons[i][0] > 0) {
                calculate_neuron(i);
                flag = 1;
            }
        }
    } while (flag);

    int found_output = 0;
    for (int i = 1; i <= n; i++) {
        if (neurons[i][0] > 0) {
            found_output = 1;
            printf("%d %d\n", i, neurons[i][0]);
        }
    }
    if (!found_output) {
        printf("NULL\n");
    }

    return 0;
}