#include <stdio.h>
#include <stdlib.h>

#define MAX_M 20
#define MAX_N 20
#define MAX_OP 400

typedef struct {
    int start;
    int end;
} Interval;

int main(){
    int m, n;
    scanf("%d %d", &m, &n);
    
    int total_ops = m * n;
    int sequence[MAX_OP];
    for(int i=0;i<total_ops;i++) {
        scanf("%d", &sequence[i]);
    }
    
    // Read machine numbers for each job's operations
    int machine_num[MAX_N+1][MAX_M+1];
    for(int job=1; job<=n; job++) {
        for(int op=1; op<=m; op++) {
            scanf("%d", &machine_num[job][op]);
        }
    }
    
    // Read processing times for each job's operations
    int proc_time[MAX_N+1][MAX_M+1];
    for(int job=1; job<=n; job++) {
        for(int op=1; op<=m; op++) {
            scanf("%d", &proc_time[job][op]);
        }
    }
    
    // Initialize machine schedules
    Interval machine_schedules[MAX_M+1][MAX_OP];
    int machine_counts[MAX_M+1];
    for(int machine=1; machine<=m; machine++) {
        machine_counts[machine] = 0;
    }
    
    // Initialize job last finish times
    int job_last_finish[MAX_N+1];
    for(int job=1; job<=n; job++) {
        job_last_finish[job] = 0;
    }
    
    // Operation indices per job
    int op_index[MAX_N+1];
    for(int job=1; job<=n; job++) {
        op_index[job] = 0;
    }
    
    // Schedule operations
    for(int i=0; i<total_ops; i++) {
        int job = sequence[i];
        op_index[job]++;
        int current_op = op_index[job];
        int machine = machine_num[job][current_op];
        int time = proc_time[job][current_op];
        int earliest_start = job_last_finish[job];
        
        // Find earliest start time on the machine
        int count = machine_counts[machine];
        int start_time = earliest_start;
        for(int j=0; j<count; j++) {
            if(start_time + time <= machine_schedules[machine][j].start){
                break;
            }
            if(start_time >= machine_schedules[machine][j].end){
                continue;
            }
            if(start_time < machine_schedules[machine][j].end){
                start_time = machine_schedules[machine][j].end;
            }
        }
        
        // After all scheduled intervals
        // No need to do anything, start_time is already set
        
        // Insert the interval into the machine's schedule in sorted order
        int finish_time = start_time + time;
        int pos = 0;
        while(pos < machine_counts[machine] && machine_schedules[machine][pos].start < start_time){
            pos++;
        }
        for(int k=machine_counts[machine]; k>pos; k--){
            machine_schedules[machine][k] = machine_schedules[machine][k-1];
        }
        machine_schedules[machine][pos].start = start_time;
        machine_schedules[machine][pos].end = finish_time;
        machine_counts[machine]++;
        
        // Update job's last finish time
        if(finish_time > job_last_finish[job]){
            job_last_finish[job] = finish_time;
        }
    }
    
    // Find the maximum finish time among all jobs
    int total_time = 0;
    for(int job=1; job<=n; job++) {
        if(job_last_finish[job] > total_time){
            total_time = job_last_finish[job];
        }
    }
    
    printf("%d\n", total_time);
    return 0;
}