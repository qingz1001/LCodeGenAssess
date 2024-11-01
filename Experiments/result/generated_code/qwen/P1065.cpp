#include <stdio.h>
#include <stdlib.h>

#define MAX_M 20
#define MAX_N 20

typedef struct {
    int machine;
    int time;
} Operation;

int compare(const void *a, const void *b) {
    return ((Operation *)a)->time - ((Operation *)b)->time;
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    int order[MAX_M * MAX_N];
    for (int i = 0; i < m * n; i++) {
        scanf("%d", &order[i]);
    }

    Operation ops[MAX_M * MAX_N];
    for (int j = 0; j < n; j++) {
        for (int k = 0; k < m; k++) {
            scanf("%d", &ops[j * m + k].machine);
            scanf("%d", &ops[j * m + k].time);
        }
    }

    int schedule[MAX_M][MAX_N];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            schedule[i][j] = -1;
        }
    }

    for (int i = 0; i < m * n; i++) {
        int op_index = order[i] - 1;
        int machine = ops[op_index].machine - 1;
        int time = ops[op_index].time;

        int earliest_time = 0;
        for (int j = 0; j < n; j++) {
            if (schedule[machine][j] != -1 && schedule[machine][j] >= earliest_time) {
                earliest_time = schedule[machine][j] + 1;
            }
        }

        for (int j = n - 1; j > 0; j--) {
            if (schedule[machine][j] == -1) {
                schedule[machine][j] = earliest_time + time;
                break;
            } else if (schedule[machine][j] < earliest_time) {
                schedule[machine][j] += time;
                break;
            }
        }
    }

    int max_time = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (schedule[i][j] > max_time) {
                max_time = schedule[i][j];
            }
        }
    }

    printf("%d\n", max_time);

    return 0;
}