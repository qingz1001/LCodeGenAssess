#include <stdio.h>
#include <stdbool.h>

#define MAX_M 20
#define MAX_N 20

int m, n;
int schedule[MAX_M * MAX_N];
int machine[MAX_N][MAX_M];
int time[MAX_N][MAX_M];
int finish_time[MAX_M];

void read_input() {
    scanf("%d %d", &m, &n);
    for (int i = 0; i < m * n; i++) {
        scanf("%d", &schedule[i]);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &machine[i][j]);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &time[i][j]);
        }
    }
}

bool can_insert(int job, int step, int machine_id, int start_time) {
    for (int i = start_time; i < start_time + time[job][step]; i++) {
        if (finish_time[machine_id] > i) return false;
    }
    return true;
}

void insert_operation(int job, int step, int machine_id, int start_time) {
    for (int i = start_time; i < start_time + time[job][step]; i++) {
        finish_time[machine_id] = i;
    }
}

int main() {
    read_input();
    int max_time = 0;
    for (int i = 0; i < m * n; i++) {
        int job = schedule[i] - 1;
        int step = 0;
        while (machine[job][step] != 0) {
            if (can_insert(job, step, machine[job][step] - 1, max_time)) {
                insert_operation(job, step, machine[job][step] - 1, max_time);
                break;
            }
            step++;
        }
        if (machine[job][step] == 0) {
            max_time++;
            i--;
            continue;
        }
        for (int j = 0; j < m; j++) {
            if (finish_time[j] > max_time) {
                max_time = finish_time[j];
            }
        }
    }
    printf("%d\n", max_time);
    return 0;
}