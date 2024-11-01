#include <stdio.h>
#include <string.h>

#define MAX_N 20
#define MAX_M 20

int m, n;
int order[MAX_N * MAX_M];
int machine[MAX_N][MAX_M];
int time[MAX_N][MAX_M];
int finish_time[MAX_N][MAX_M];
int machine_time[MAX_M];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d", &m, &n);

    for (int i = 0; i < m * n; i++) {
        scanf("%d", &order[i]);
        order[i]--;  // 转为0-based索引
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &machine[i][j]);
            machine[i][j]--;  // 转为0-based索引
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &time[i][j]);
        }
    }

    memset(finish_time, 0, sizeof(finish_time));
    memset(machine_time, 0, sizeof(machine_time));

    for (int i = 0; i < m * n; i++) {
        int job = order[i];
        int step = 0;
        while (finish_time[job][step] > 0) step++;

        int mach = machine[job][step];
        int start_time = max(machine_time[mach], step > 0 ? finish_time[job][step-1] : 0);
        int end_time = start_time + time[job][step];

        finish_time[job][step] = end_time;
        machine_time[mach] = end_time;
    }

    int total_time = 0;
    for (int i = 0; i < m; i++) {
        total_time = max(total_time, machine_time[i]);
    }

    printf("%d\n", total_time);

    return 0;
}