#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define INF 1000000000

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    int *a = (int*)malloc((N+1)*sizeof(int));
    for(int i=1;i<=N;i++) scanf("%d", &a[i]);
    int *d = (int*)malloc((N+1)*sizeof(int));
    d[0] =0;
    for(int i=1;i<=N;i++) d[i] = d[i-1] + (a[i]==1 ?1 :-1);
    int shift = N;
    int size = 2*N +1;
    int *min_dp_d = (int*)malloc(size*sizeof(int));
    for(int i=0;i<size;i++) min_dp_d[i] = INF;
    min_dp_d[d[0] + shift] =0;
    int *dp = (int*)malloc((N+1)*sizeof(int));
    dp[0] =0;
    int run_start =1;
    for(int i=1;i<=N;i++){
        // Find min over [d[i]-M, d[i]+M]
        int di = d[i];
        int low = di - M;
        if(low < -N) low = -N;
        int high = di + M;
        if(high > N) high = N;
        int temp_min = INF;
        for(int dj = low; dj <= high; dj++){
            if(min_dp_d[dj + shift] < temp_min){
                temp_min = min_dp_d[dj + shift];
                if(temp_min ==0) break;
            }
        }
        dp[i] = temp_min +1;
        // Handle all same
        if(i ==1 || a[i] !=a[i-1]){
            run_start =i;
        }
        if(dp[run_start -1] +1 < dp[i]){
            dp[i] = dp[run_start -1] +1;
        }
        // Update min_dp_d
        if(dp[i] < min_dp_d[di + shift]){
            min_dp_d[di + shift] = dp[i];
        }
    }
    printf("%d\n", dp[N]);
    free(a);
    free(d);
    free(min_dp_d);
    free(dp);
    return 0;
}