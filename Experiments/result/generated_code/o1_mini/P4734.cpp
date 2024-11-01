#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    scanf("%d", &n);
    int *v = (int*)malloc(n * sizeof(int));
    for(int i=0;i<n;i++) scanf("%d", &v[i]);
    
    int step_count = (n -1)/2;
    long long max_sum = 0;
    
    for(int i=0;i<n;i++){
        // Compute sum_clk
        long long sum_clk = 0;
        int j = (i -1 +n)%n;
        for(int k=0; k<step_count; k++){
            sum_clk += v[j];
            j = (j -2 +n)%n;
        }
        
        // Compute sum_anticlk
        long long sum_anticlk = 0;
        j = (i +1)%n;
        for(int k=0; k<step_count; k++){
            sum_anticlk += v[j];
            j = (j +2)%n;
        }
        
        // Calculate sum_i
        long long sum_i = v[i] + (sum_clk < sum_anticlk ? sum_clk : sum_anticlk);
        if(sum_i > max_sum) max_sum = sum_i;
    }
    
    printf("%lld\n", max_sum);
    free(v);
    return 0;
}