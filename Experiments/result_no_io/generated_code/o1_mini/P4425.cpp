#include <stdio.h>
#include <stdlib.h>

// Function to compute prefix_max
void compute_prefix_max(long long *prefix_max, long long *T, int n){
    prefix_max[0] = T[0] + 0;
    for(int i=1;i<n;i++){
        if(T[i]+i > prefix_max[i-1]){
            prefix_max[i] = T[i]+i;
        }
        else{
            prefix_max[i] = prefix_max[i-1];
        }
    }
}

// Function to compute suffix_max
void compute_suffix_max(long long *suffix_max, long long *T, int n){
    suffix_max[n-1] = T[n-1] + (n-1);
    for(int i=n-2;i>=0;i--){
        if(T[i]+i > suffix_max[i+1]){
            suffix_max[i] = T[i]+i;
        }
        else{
            suffix_max[i] = suffix_max[i+1];
        }
    }
}

int main(){
    int n, m, p;
    scanf("%d %d %d", &n, &m, &p);
    long long *T = (long long*)malloc(n * sizeof(long long));
    for(int i=0;i<n;i++) scanf("%lld", &T[i]);
    
    long long *prefix_max = (long long*)malloc(n * sizeof(long long));
    long long *suffix_max = (long long*)malloc(n * sizeof(long long));
    
    compute_prefix_max(prefix_max, T, n);
    compute_suffix_max(suffix_max, T, n);
    
    long long min_f = -1;
    for(int s0=0;s0<n;s0++){
        long long current;
        if(s0 ==0){
            current = suffix_max[0];
        }
        else{
            long long a = suffix_max[s0];
            long long b = prefix_max[s0-1] + n;
            current = (a > b) ? a : b;
            current -= s0;
        }
        if(min_f == -1 || current < min_f){
            min_f = current;
        }
    }
    printf("%lld\n", min_f);
    
    long long LastAns = (p==1) ? min_f : 0;
    
    for(int i=0;i<m;i++){
        long long x, y;
        scanf("%lld %lld", &x, &y);
        if(p ==1){
            long long x_prime = x ^ LastAns;
            long long y_prime = y ^ LastAns;
            if(x_prime <1 || x_prime >n){
                // Invalid, but problem guarantees input is valid
            }
            T[x_prime-1] = y_prime;
        }
        else{
            if(x <1 || x >n){
                // Invalid, but problem guarantees input is valid
            }
            T[x-1] = y;
        }
        compute_prefix_max(prefix_max, T, n);
        compute_suffix_max(suffix_max, T, n);
        
        // Recompute min_f
        long long current_min_f = -1;
        for(int s0=0;s0<n;s0++){
            long long current;
            if(s0 ==0){
                current = suffix_max[0];
            }
            else{
                long long a = suffix_max[s0];
                long long b = prefix_max[s0-1] + n;
                current = (a > b) ? a : b;
                current -= s0;
            }
            if(current_min_f == -1 || current < current_min_f){
                current_min_f = current;
            }
        }
        printf("%lld\n", current_min_f);
        if(p ==1){
            LastAns = current_min_f;
        }
    }
    
    free(T);
    free(prefix_max);
    free(suffix_max);
    return 0;
}