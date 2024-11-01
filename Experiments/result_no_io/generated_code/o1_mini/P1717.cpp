#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    scanf("%d", &n);
    
    int H;
    scanf("%d", &H);
    int total_time = H * 12;
    
    int f[25];
    for(int i=0;i<n;i++) scanf("%d", &f[i]);
    
    int d[25];
    for(int i=0;i<n;i++) scanf("%d", &d[i]);
    
    int t[24];
    for(int i=0;i<n-1;i++) scanf("%d", &t[i]);
    
    int max_total = 0;
    
    for(int k=1; k<=n; k++){
        // Calculate time to reach lake k
        int time_to_k = 0;
        for(int i=0;i<k-1;i++) time_to_k += t[i];
        if(time_to_k > total_time) continue;
        int remaining = total_time - time_to_k;
        
        // Initialize current fish for lakes 1 to k
        int current_f[25];
        for(int i=0;i<k;i++) current_f[i] = f[i];
        
        int total_fish = 0;
        for(int i=0;i<remaining;i++){
            // Find lake with maximum current_f
            int best = 0;
            for(int j=1; j<k; j++) if(current_f[j] > current_f[best]) best = j;
            if(current_f[best] == 0) break;
            total_fish += current_f[best];
            current_f[best] -= d[best];
            if(current_f[best] < 0) current_f[best] = 0;
        }
        if(total_fish > max_total) max_total = total_fish;
    }
    
    printf("%d\n", max_total);
    return 0;
}