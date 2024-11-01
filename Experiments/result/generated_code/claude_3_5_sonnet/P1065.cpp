#include <stdio.h>
#include <string.h>

#define MAX_N 20
#define MAX_M 20

int m, n;
int order[MAX_N * MAX_M];
int machine[MAX_N][MAX_M];
int time[MAX_N][MAX_M];
int machine_end_time[MAX_M];
int work_end_time[MAX_N];

int main() {
    scanf("%d %d", &m, &n);
    
    for (int i = 0; i < m * n; i++) {
        scanf("%d", &order[i]);
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
    
    memset(machine_end_time, 0, sizeof(machine_end_time));
    memset(work_end_time, 0, sizeof(work_end_time));
    
    int total_time = 0;
    
    for (int i = 0; i < m * n; i++) {
        int work = order[i] - 1;
        int process = 0;
        while (machine[work][process] != machine[work][process]) {
            process++;
        }
        
        int start_time = (work_end_time[work] > machine_end_time[machine[work][process] - 1]) ? 
                          work_end_time[work] : machine_end_time[machine[work][process] - 1];
        
        int end_time = start_time + time[work][process];
        
        work_end_time[work] = end_time;
        machine_end_time[machine[work][process] - 1] = end_time;
        
        if (end_time > total_time) {
            total_time = end_time;
        }
    }
    
    printf("%d\n", total_time);
    
    return 0;
}