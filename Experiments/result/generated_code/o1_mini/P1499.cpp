#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    int ni;
    int Ti; // in seconds
    int ti;
} Patrol;

int time_to_seconds(char *s) {
    int h, m, sec;
    sscanf(s, "%2d%2d%2d", &h, &m, &sec);
    return h * 3600 + m * 60 + sec;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    Patrol patrols[m];
    for(int i=0;i<m;i++){
        char time_str[7];
        scanf("%d %s %d", &patrols[i].ni, time_str, &patrols[i].ti);
        patrols[i].Ti = time_to_seconds(time_str);
    }
    // Target car starts at 06:00:00
    int start_time = 6 * 3600;
    // Each segment is 10 km
    int segments = n -1;
    // Min speed 60 km/h, max 120 km/h
    // Convert speeds to m/s: 60 km/h = 16.6667 m/s, 120 km/h = 33.3333 m/s
    // Time per segment: 10 km / speed = 10000 / speed seconds
    // Since speeds are continuous, but arrival times are integer seconds, we can iterate over possible arrival times
    // for each segment, arrival time must be integer
    // To minimize meetings, let's assume target car chooses its speed such that it arrives at each toll gate at integer seconds
    // We'll calculate total time and number of meets
    // To find the earliest arrival time with minimum meets
    // Since each segment time is between 300 (10km / 120 km/h * 3600) and 600 seconds (10km / 60 km/h * 3600)
    // Total time is between 300*(n-1) and 600*(n-1)
    // Starting from start_time + 300*(n-1)
    // to start_time + 600*(n-1)
    int min_total_time = start_time + 300 * segments;
    int max_total_time = start_time + 600 * segments;
    int best_meet = m+1;
    int best_arrival = max_total_time;
    for(int total_time = min_total_time; total_time <= max_total_time; total_time++){
        // Compute arrival times at each toll gate
        // t0 = start_time
        // tn = total_time
        // Each segment time ti = (total_time - start_time) / segments
        // But needs to be integer seconds and between 300 and 600
        // So we need to distribute the total_time into segments with individual times between 300 and 600
        // This is equivalent to partitioning total_time - start_time into 'segments' parts, each between 300 and 600
        // Let's use dynamic programming to check if it's possible
        int target = total_time - start_time;
        int dp[51][(600-300)*50+1];
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;
        for(int i=0;i<segments;i++){
            for(int j=0; j <= target; j++){
                if(dp[i][j]){
                    for(int t=300;t<=600;t++){
                        if(j + t <= target){
                            dp[i+1][j+t] = 1;
                        }
                    }
                }
            }
        }
        if(!dp[segments][target]) continue;
        // Now, find one possible segment times
        int seg_times[50];
        int rem = target;
        int possible = 0;
        for(int i=segments-1;i>=0;i--){
            for(int t=300;t<=600;t++){
                if(rem - t >=0 && dp[i][rem - t]){
                    seg_times[i] = t;
                    rem -= t;
                    break;
                }
            }
        }
        if(rem !=0) continue;
        // Now, compute arrival times
        int arrival_times[n];
        arrival_times[0] = start_time;
        for(int i=1;i<n;i++){
            arrival_times[i] = arrival_times[i-1] + seg_times[i-1];
        }
        int arrival_final = arrival_times[n-1];
        // Now, check meetings
        int meets =0;
        for(int i=0;i<m;i++){
            // Patrol car i departs from patrols[i].ni at patrols[i].Ti and takes patrols[i].ti to reach next gate
            // So it travels from ni to ni+1 from Ti to Ti + ti
            // Check if target car and patrol car are on the same segment at overlapping times
            if(patrols[i].ni >= n) continue;
            // Target car passes from ni to ni+1 between arrival_times[ni-1] to arrival_times[ni]
            int target_start = arrival_times[patrols[i].ni -1];
            int target_end = arrival_times[patrols[i].ni];
            int patrol_start = patrols[i].Ti;
            int patrol_end = patrols[i].Ti + patrols[i].ti;
            // Check if time intervals overlap
            if(!(target_end <= patrol_start || patrol_end <= target_start)){
                meets++;
                continue;
            }
            // Also check if they arrive at the same time at ni or ni+1
            if(target_start == patrol_start && patrols[i].ni ==1){
                // They both depart from gate1 at same time, but this doesn't count as meeting
            } else {
                if(target_start == patrol_start && patrols[i].ni >=1){
                    meets++;
                    continue;
                }
            }
            if(target_end == patrol_end){
                meets++;
                continue;
            }
        }
        if(meets < best_meet || (meets == best_meet && arrival_final < best_arrival)){
            best_meet = meets;
            best_arrival = arrival_final;
        }
    }
    // Convert best_arrival to HHMMSS
    int hh = best_arrival / 3600;
    int mm = (best_arrival % 3600) / 60;
    int ss = best_arrival % 60;
    printf("%d\n", best_meet);
    printf("%02d%02d%02d\n", hh, mm, ss);
    return 0;
}