#include <stdio.h>
#include <stdlib.h>

#define MAX_M 20
#define MAX_N 20

int m, n;
int order[MAX_M * MAX_N];
int machine[MAX_N][MAX_M];
int time[MAX_N][MAX_M];
int job_start[MAX_N];
int machine_time[MAX_M];

int main() {
    scanf("%d %d", &m, &n);
    for (int i = 0; i < m * n; i++) {
        scanf("%d", &order[i]);
        order[i]--; // Convert to 0-based index
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &machine[i][j]);
            machine[i][j]--; // Convert to 0-based index
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &time[i][j]);
        }
    }

    for (int i = 0; i < m * n; i++) {
        int job = order[i];
        int step = job_start[job];
        int machine_id = machine[job][step];
        int process_time = time[job][step];

        int start_time = job_start[job];
        for (int t = start_time; t < m * n * 20; t++) {
            if (t + process_time <= machine_time[machine_id]) {
                continue;
            }
            int can_insert = 1;
            for (int tt = t; tt < t + process_time; tt++) {
                if (tt < machine_time[machine_id]) {
                    can_insert = 0;
                    break;
                }
            }
            if (can_insert) {
                for (int tt = t; tt < t + process_time; tt++) {
                    machine_time[machine_id] = tt + 1;
                }
                job_start[job] = t + process_time;
                break;
            }
        }
    }

    int max_time = 0;
    for (int i = 0; i < m; i++) {
        if (machine_time[i] > max_time) {
            max_time = machine_time[i];
        }
    }

    printf("%d\n", max_time);
    return 0;
}