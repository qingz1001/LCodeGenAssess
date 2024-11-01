#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000000
#define MAXQ (1000000 + 1)

int main(){
    int n, k;
    scanf("%d %d", &n, &k);
    
    int *a = (int*)malloc(n * sizeof(int));
    for(int i=0;i<n;i++) scanf("%d", &a[i]);
    
    // Deque for min
    int *dq_min = (int*)malloc(MAXQ * sizeof(int));
    int head_min = 0, tail_min = 0;
    
    // Deque for max
    int *dq_max = (int*)malloc(MAXQ * sizeof(int));
    int head_max = 0, tail_max = 0;
    
    // To store results
    int output_size = n - k +1;
    int *min_out = (int*)malloc(output_size * sizeof(int));
    int *max_out = (int*)malloc(output_size * sizeof(int));
    int out_idx =0;
    
    for(int i=0;i<n;i++){
        // Maintain min deque
        while(tail_min > head_min && a[i] <= a[dq_min[tail_min -1]]) tail_min--;
        dq_min[tail_min++] = i;
        // Remove out of window
        while(head_min < tail_min && dq_min[head_min] <= i - k) head_min++;
        
        // Maintain max deque
        while(tail_max > head_max && a[i] >= a[dq_max[tail_max -1]]) tail_max--;
        dq_max[tail_max++] = i;
        // Remove out of window
        while(head_max < tail_max && dq_max[head_max] <= i - k) head_max++;
        
        // If window is complete
        if(i >= k -1){
            min_out[out_idx] = a[dq_min[head_min]];
            max_out[out_idx] = a[dq_max[head_max]];
            out_idx++;
        }
    }
    
    // Print min
    for(int i=0;i<output_size;i++){
        printf("%d", min_out[i]);
        if(i != output_size -1) printf(" ");
    }
    printf("\n");
    
    // Print max
    for(int i=0;i<output_size;i++){
        printf("%d", max_out[i]);
        if(i != output_size -1) printf(" ");
    }
    printf("\n");
    
    // Free memory
    free(a);
    free(dq_min);
    free(dq_max);
    free(min_out);
    free(max_out);
    
    return 0;
}