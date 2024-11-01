#include <stdio.h>
#include <stdlib.h>

#define MAX_M 20
#define MAX_N 20

int m, n;
int sequence[MAX_M * MAX_N];
int machine[MAX_N][MAX_M];
int time[MAX_N][MAX_M];
int last_finish_time[MAX_N];
int machine_time[MAX_M];

int main() {
    scanf("%d %d", &m, &n);
    for (int i = 0; i < m * n; i++) {
        scanf("%d", &sequence[i]);
        sequence[i]--; // 0-based index
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &machine[i][j]);
            machine[i][j]--; // 0-based index
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &time[i][j]);
        }
    }

    for (int i = 0; i < m * n; i++) {
        int job = sequence[i];
        int step = 0;
        while (machine[job][step] == -1) {
            step++;
        }
        int machine_id = machine[job][step];
        int process_time = time[job][step];

        int start_time = last_finish_time[job];
        if (start_time < machine_time[machine_id]) {
            start_time = machine_time[machine_id];
        }

        last_finish_time[job] = start_time + process_time;
        machine_time[machine_id] = start_time + process_time;

        machine[job][step] = -1; // Mark this step as done
    }

    int total_time = 0;
    for (int i = 0; i < m; i++) {
        if (machine_time[i] > total_time) {
            total_time = machine_time[i];
        }
    }

    printf("%d\n", total_time);
    return 0;
}