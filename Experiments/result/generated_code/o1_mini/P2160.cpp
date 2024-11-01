#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    scanf("%d", &n);
    int h[n];
    int t[n];
    for(int i=0;i<n;i++) scanf("%d %d", &h[i], &t[i]);
    long long min_S = (long long)300*3*2100; // Initialize with a large value
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            // Compute sum_h
            int max_h = 0;
            long long sum_t_remaining = 0;
            for(int k=0;k<n;k++){
                if(k != i && k != j){
                    if(h[k] > max_h) max_h = h[k];
                    sum_t_remaining += t[k];
                }
            }
            int sum_h = h[i] + h[j] + max_h;
            long long max_thickness = t[i] > t[j] ? t[i] : t[j];
            if(sum_t_remaining > max_thickness) max_thickness = sum_t_remaining;
            long long S = (long long)sum_h * max_thickness;
            if(S < min_S) min_S = S;
        }
    }
    printf("%lld\n", min_S);
    return 0;
}