#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_GATE 50
#define MAX_PATROLS 300
#define MAX_TIME 86400
#define INF 1000000

typedef struct {
    int T; // departure time in seconds
    int t; // traversal time in seconds
} PatrolCar;

// Function to convert HHMMSS string to seconds
int time_to_seconds(char *s) {
    int h, m, sec;
    sscanf(s, "%2d%2d%2d", &h, &m, &sec);
    return h * 3600 + m * 60 + sec;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    
    PatrolCar patrols[MAX_GATE][MAX_PATROLS];
    int patrol_count[MAX_GATE];
    for(int k=1; k<=n-1; k++) patrol_count[k]=0;
    
    for(int i=0; i<m; i++){
        int ni, ti;
        char Ti_str[7];
        scanf("%d %s %d", &ni, Ti_str, &ti);
        int Ti = time_to_seconds(Ti_str);
        patrols[ni][patrol_count[ni]++] = (PatrolCar){Ti, ti};
    }
    
    int current_counts[MAX_TIME+1];
    for(int t=0; t<=MAX_TIME; t++) current_counts[t] = INF;
    current_counts[21600] = 0; // 6:00:00 in seconds
    
    int next_counts[MAX_TIME+1];
    
    for(int k=1; k<=n-1; k++){
        for(int t=0; t<=MAX_TIME; t++) next_counts[t] = INF;
        
        for(int t=0; t<=MAX_TIME; t++){
            if(current_counts[t] < INF){
                for(int s=300; s<=600; s++){
                    int new_time = t + s;
                    if(new_time > MAX_TIME) continue;
                    int count = 0;
                    for(int p=0; p<patrol_count[k]; p++){
                        int patrol_end = patrols[k][p].T + patrols[k][p].t;
                        if(new_time == patrol_end){
                            count++;
                        }
                        else if(t < patrol_end && patrols[k][p].T < new_time){
                            count++;
                        }
                    }
                    int total_count = current_counts[t] + count;
                    if(total_count < next_counts[new_time]){
                        next_counts[new_time] = total_count;
                    }
                    else if(total_count == next_counts[new_time]){
                        // Keep the earliest time, which is already satisfied
                    }
                }
            }
        }
        // Update current_counts
        for(int t=0; t<=MAX_TIME; t++) current_counts[t] = next_counts[t];
    }
    
    // Find minimal count and earliest time
    int min_count = INF;
    int earliest_time = 0;
    for(int t=0; t<=MAX_TIME; t++){
        if(current_counts[t] < min_count){
            min_count = current_counts[t];
            earliest_time = t;
        }
        else if(current_counts[t] == min_count && t < earliest_time){
            earliest_time = t;
        }
    }
    
    // Convert earliest_time to HHMMSS
    int hh, mm, ss;
    hh = earliest_time / 3600;
    mm = (earliest_time % 3600) / 60;
    ss = earliest_time % 60;
    
    printf("%d\n", min_count);
    printf("%02d%02d%02d\n", hh, mm, ss);
    
    return 0;
}