#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    scanf("%d", &n);
    int H;
    scanf("%d", &H);
    int f[n+1];
    for(int i=1;i<=n;i++) scanf("%d", &f[i]);
    int d[n+1];
    for(int i=1;i<=n;i++) scanf("%d", &d[i]);
    int t[n];
    for(int i=1;i<n;i++) scanf("%d", &t[i]);
    
    int max_total_fish = 0;
    for(int k=1;k<=n;k++){
        // Calculate walking time
        int walk_time =0;
        for(int i=1;i<k;i++) walk_time += 5 * t[i];
        if(walk_time > H*60) continue;
        // Calculate fishing time
        int fishing_time = H*60 - walk_time;
        int fishing_steps = fishing_time /5;
        // Initialize current_fish
        int current_fish[k+1];
        for(int i=1;i<=k;i++) current_fish[i] = f[i];
        int total_fish =0;
        for(int s=0;s<fishing_steps;s++){
            // Find lake with max current_fish
            int max_fish = -1;
            int lake = 1;
            for(int i=1;i<=k;i++){
                if(current_fish[i] > max_fish){
                    max_fish = current_fish[i];
                    lake = i;
                }
            }
            if(max_fish <=0) break;
            total_fish += current_fish[lake];
            current_fish[lake] -= d[lake];
            if(current_fish[lake] <0) current_fish[lake] =0;
        }
        if(total_fish > max_total_fish) max_total_fish = total_fish;
    }
    printf("%d\n", max_total_fish);
    return 0;
}