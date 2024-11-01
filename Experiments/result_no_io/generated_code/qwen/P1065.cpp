#include <stdio.h>
#include <stdlib.h>

#define MAX_M 19
#define MAX_N 19
#define MAX_TIME 21

typedef struct {
    int machine;
    int time;
} Operation;

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    int order[MAX_M * MAX_N];
    for (int i = 0; i < m * n; i++) {
        scanf("%d", &order[i]);
    }

    int machine_order[MAX_N][MAX_M];
    int time[MAX_N][MAX_M];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &machine_order[i][j]);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &time[i][j]);
        }
    }

    Operation schedule[MAX_M][MAX_N];
    int current_time[MAX_M] = {0};

    for (int i = 0; i < m * n; i++) {
        int op_index = order[i] - 1;
        int j = op_index / n;
        int k = op_index % n;

        int machine = machine_order[j][k];
        int t = time[j][k];

        int insert_time = current_time[machine];
        for (int t2 = current_time[machine]; t2 <= insert_time + t; t2++) {
            if (schedule[machine][t2].time == 0) {
                insert_time = t2;
                break;
            }
        }

        for (int t2 = insert_time; t2 > 0; t2--) {
            schedule[machine][t2] = schedule[machine][t2 - 1];
        }

        schedule[machine][insert_time].machine = machine;
        schedule[machine][insert_time].time = t;

        current_time[machine] += t;
    }

    int max_time = 0;
    for (int i = 0; i < m; i++) {
        if (current_time[i] > max_time) {
            max_time = current_time[i];
        }
    }

    printf("%d\n", max_time);
    return 0;
}