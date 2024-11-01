#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Function to compute floor division for negative numbers
long long floor_div2(long long x) {
    if (x >= 0) {
        return x / 2;
    } else {
        if (x % 2 == 0) {
            return x / 2;
        } else {
            return (x / 2) - 1;
        }
    }
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    // Initialize global_max and global_min
    long long global_max[11];
    long long global_min_val[11];
    for(int k=0; k<=m; k++){
        global_max[k] = LLONG_MIN;
        global_min_val[k] = LLONG_MAX;
    }
    for(int i=0; i<n; i++){
        long long a;
        scanf("%lld", &a);
        // Compute max_val
        long long max_val[11];
        max_val[0] = a;
        for(int k=1; k<=m; k++){
            long long option1 = max_val[k-1] * 2;
            long long option2 = max_val[k-1] + 2;
            if(option1 > option2){
                max_val[k] = option1;
            }
            else{
                max_val[k] = option2;
            }
        }
        // Compute min_val
        long long min_val[11];
        min_val[0] = a;
        for(int k=1; k<=m; k++){
            long long tmp1 = floor_div2(min_val[k-1]);
            long long tmp2 = min_val[k-1] - 2;
            if(tmp1 < tmp2){
                min_val[k] = tmp1;
            }
            else{
                min_val[k] = tmp2;
            }
        }
        // Update global_max and global_min
        for(int k=0; k<=m; k++){
            if(max_val[k] > global_max[k]){
                global_max[k] = max_val[k];
            }
            if(min_val[k] < global_min_val[k]){
                global_min_val[k] = min_val[k];
            }
        }
    }
    // Compute the maximum range
    long long result = LLONG_MIN;
    for(int l=0; l<=m; l++){
        if(m - l > m || m - l <0){
            continue;
        }
        long long current_range = global_max[l] - global_min_val[m - l];
        if(current_range > result){
            result = current_range;
        }
    }
    printf("%lld\n", result);
    return 0;
}