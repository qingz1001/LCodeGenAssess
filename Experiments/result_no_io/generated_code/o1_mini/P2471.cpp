#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Function to compute floor of log2(n)
void compute_logs(int n, int* logs) {
    logs[1] = 0;
    for(int i=2; i<=n; i++) {
        logs[i] = logs[i/2] + 1;
    }
}

int main(){
    int n;
    scanf("%d", &n);
    
    int64_t *y = (int64_t*)malloc(n * sizeof(int64_t));
    int64_t *r = (int64_t*)malloc(n * sizeof(int64_t));
    
    for(int i=0; i<n; i++) {
        scanf("%lld %lld", &y[i], &r[i]);
    }
    
    // Compute log table
    int logn = 0;
    while((1 << (logn+1)) <= n) logn++;
    
    int *logs = (int*)malloc((n+1) * sizeof(int));
    compute_logs(n, logs);
    
    // Build Sparse Table
    int **st = (int**)malloc((logn+1) * sizeof(int*));
    for(int i=0; i<=logn; i++) {
        st[i] = (int*)malloc(n * sizeof(int));
    }
    
    for(int i=0; i<n; i++) {
        st[0][i] = (int)r[i];
    }
    
    for(int k=1; k<=logn; k++) {
        for(int i=0; i + (1 << k) <= n; i++) {
            if(st[k-1][i] > st[k-1][i + (1 << (k-1))])
                st[k][i] = st[k-1][i];
            else
                st[k][i] = st[k-1][i + (1 << (k-1))];
        }
    }
    
    int m;
    scanf("%d", &m);
    
    while(m--){
        int64_t Y, X;
        scanf("%lld %lld", &Y, &X);
        
        // Binary search for Y
        int left = 0, right = n-1, idx_Y = -1;
        while(left <= right){
            int mid = left + (right - left)/2;
            if(y[mid] == Y){
                idx_Y = mid;
                break;
            }
            else if(y[mid] < Y){
                left = mid +1;
            }
            else{
                right = mid -1;
            }
        }
        
        // Binary search for X
        left = 0; right = n-1;
        int idx_X = -1;
        while(left <= right){
            int mid = left + (right - left)/2;
            if(y[mid] == X){
                idx_X = mid;
                break;
            }
            else if(y[mid] < X){
                left = mid +1;
            }
            else{
                right = mid -1;
            }
        }
        
        if(idx_Y != -1 && idx_X != -1){
            if(r[idx_X] < r[idx_Y]){
                printf("false\n");
                continue;
            }
            
            if(idx_X - idx_Y -1 <0){
                printf("true\n");
                continue;
            }
            
            // Find maximum rainfall in (idx_Y+1, idx_X-1)
            int L = idx_Y +1;
            int R = idx_X -1;
            int current_max = 0;
            if(L <= R){
                int length = R - L +1;
                int k = logs[length];
                int max1 = st[k][L];
                int max2 = st[k][R - (1<<k) +1];
                current_max = (max1 > max2) ? max1 : max2;
            }
            
            if(L > R || current_max < (int)r[idx_X]){
                // Check if all years between Y and X are present
                if(y[idx_X] - y[idx_Y] == X - Y){
                    printf("true\n");
                }
                else{
                    printf("maybe\n");
                }
            }
            else{
                printf("false\n");
            }
        }
        else{
            printf("maybe\n");
        }
    }
    
    // Free memory
    for(int i=0; i<=logn; i++) {
        free(st[i]);
    }
    free(st);
    free(logs);
    free(y);
    free(r);
    
    return 0;
}