#include <stdio.h>
#include <string.h>

#define MAX_M 20
#define MAX_N 20

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    
    int schedule[MAX_M * MAX_N];
    for (int i = 0; i < m * n; i++) {
        scanf("%d", &schedule[i]);
    }
    
    int machine[MAX_M][MAX_N]; // machine[i][j] 表示工件 i 的第 j 道工序使用的机器编号
    int time[MAX_M][MAX_N];    // time[i][j] 表示工件 i 的第 j 道工序的加工时间
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
    
    int finish_time[MAX_M]; // finish_time[i] 表示机器 i 完成当前任务的时间
    memset(finish_time, 0, sizeof(finish_time));
    
    int total_time = 0;
    for (int i = 0; i < m * n; i++) {
        int job = schedule[i] - 1; // 将工件编号从 1-based 转换为 0-based
        int op = 0;
        while (op < m && machine[job][op] != -1) {
            op++;
        }
        if (op == m) {
            continue; // 工件的所有工序都已安排
        }
        
        int machine_id = machine[job][op];
        int start_time = finish_time[machine_id];
        int end_time = start_time + time[job][op];
        
        // 找到插入位置
        int insert_pos = -1;
        for (int t = start_time; t < end_time; t++) {
            int conflict = 0;
            for (int j = 0; j < m; j++) {
                if (finish_time[j] > t) {
                    conflict = 1;
                    break;
                }
            }
            if (!conflict) {
                insert_pos = t;
                break;
            }
        }
        
        if (insert_pos == -1) {
            insert_pos = end_time;
        }
        
        // 更新机器完成时间
        finish_time[machine_id] = insert_pos + time[job][op];
        total_time = finish_time[machine_id];
    }
    
    printf("%d\n", total_time);
    return 0;
}