#include <stdio.h>
#include <stdlib.h>

int main(){
    int m, n;
    scanf("%d %d", &m, &n);
    
    int total_ops = m * n;
    int schedule[400];
    for(int i=0;i<total_ops;i++) {
        scanf("%d", &schedule[i]);
    }
    
    // machines[j][k]: job j, operation k
    int machines[20][20];
    for(int j=0; j<n; j++) {
        for(int k=0; k<m; k++) {
            scanf("%d", &machines[j][k]);
        }
    }
    
    int times[20][20];
    for(int j=0; j<n; j++) {
        for(int k=0; k<m; k++) {
            scanf("%d", &times[j][k]);
        }
    }
    
    int job_ready[20];
    for(int j=0; j<n; j++) job_ready[j] = 0;
    
    int machine_ready_time[20];
    for(int j=0; j<m; j++) machine_ready_time[j] = 0;
    
    int op_index[20];
    for(int j=0; j<n; j++) op_index[j] = 0;
    
    int total_time = 0;
    
    for(int i=0; i<total_ops; i++) {
        int job = schedule[i] -1;
        int op = op_index[job];
        int machine = machines[job][op] -1;
        int proc_time = times[job][op];
        
        int start = job_ready[job] > machine_ready_time[machine] ? job_ready[job] : machine_ready_time[machine];
        int finish = start + proc_time;
        
        job_ready[job] = finish;
        machine_ready_time[machine] = finish;
        
        if(finish > total_time) total_time = finish;
        
        op_index[job]++;
    }
    
    printf("%d\n", total_time);
    
    return 0;
}