#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef long long ll;

int main(){
    int N;
    scanf("%d", &N);
    int *M = (int*)malloc((N+1)*sizeof(int));
    double *prefix = (double*)malloc((N+1)*sizeof(double));
    prefix[0] = 0.0;
    for(int i=1;i<=N;i++){
        scanf("%d", &M[i]);
        prefix[i] = prefix[i-1] + M[i];
    }
    double Total = prefix[N];
    double low = 1.0, high = 10000.0;
    int iterations = 50;
    while(iterations--){
        double mid = (low + high) / 2.0;
        double min_prev = prefix[1] - mid * 1.0;
        int flag = 0;
        for(int j=2; j<=N-1; j++){
            double current = prefix[j] - mid * j;
            if(current - min_prev >= -1e-9){
                flag = 1;
                break;
            }
            if(prefix[j] - mid * j < min_prev){
                min_prev = prefix[j] - mid * j;
            }
        }
        if(flag){
            low = mid;
        }
        else{
            high = mid;
        }
    }
    double mid_max = low;
    // Find the subarray
    double min_prev = prefix[1] - mid_max * 1.0;
    int min_idx =1;
    double remaining_average = 1e18;
    for(int j=2; j<=N-1; j++){
        double current = prefix[j] - mid_max * j;
        if(current - min_prev >= -1e-9){
            // Subarray from min_idx+1 to j
            double sum_removed = prefix[j] - prefix[min_idx];
            int len_removed = j - min_idx;
            double rem = (Total - sum_removed)/(N - len_removed);
            if(rem < remaining_average){
                remaining_average = rem;
            }
        }
        if(prefix[j] - mid_max * j < min_prev){
            min_prev = prefix[j] - mid_max * j;
            min_idx = j;
        }
    }
    // Handle cases where no subarray is found, though problem states at least one removal
    // To ensure, set remaining_average to Total - any single removal
    if(remaining_average == 1e18){
        // Remove one machine from [2, N-1], choose the one with max M[i]
        int max_idx =2;
        for(int i=3;i<=N-1;i++) if(M[i] > M[max_idx]) max_idx =i;
        double sum_removed = M[max_idx];
        int len_removed =1;
        remaining_average = (Total - sum_removed)/(N - len_removed);
    }
    // Round to three decimal places
    remaining_average = floor(remaining_average * 1000.0 + 0.5) / 1000.0;
    printf("%.3lf\n", remaining_average);
    free(M);
    free(prefix);
    return 0;
}