#include <stdio.h>
#include <stdlib.h>

// Comparator for qsort
int cmp_ll(const void *a, const void *b){
    long long aa = *(long long*)a;
    long long bb = *(long long*)b;
    if(aa < bb) return -1;
    else if (aa > bb) return 1;
    else return 0;
}

int main(){
    int n;
    scanf("%d", &n);
    long long *a = (long long*)malloc(n * sizeof(long long));
    for(int i=0;i<n;i++) scanf("%lld", &a[i]);
    qsort(a, n, sizeof(long long), cmp_ll);
    
    // Count unique elements and their frequencies
    int unique_cnt =0;
    long long *unique_a = (long long*)malloc(n * sizeof(long long));
    int *f = (int*)malloc(n * sizeof(int));
    if(n >0){
        unique_a[0] = a[0];
        f[0] =1;
        unique_cnt =1;
        for(int i=1;i<n;i++){
            if(a[i] == unique_a[unique_cnt-1]){
                f[unique_cnt-1]++;
            }
            else{
                unique_a[unique_cnt] = a[i];
                f[unique_cnt] =1;
                unique_cnt++;
            }
        }
    }
    
    // Calculate minimal number of groups g
    int g =0;
    long long prev_a =0;
    int prev_end =0;
    for(int i=0;i<unique_cnt;i++){
        long long current_a = unique_a[i];
        int current_f = f[i];
        int extend =0;
        if(i >0 && current_a == prev_a +1){
            if(prev_end < current_f){
                extend = prev_end;
            }
            else{
                extend = current_f;
            }
            // Alternatively, simply the minimum
            if(prev_end < current_f){
                extend = prev_end;
            }
            else{
                extend = current_f;
            }
            extend = (prev_end < current_f) ? prev_end : current_f;
        }
        // Assign extend as min(prev_end, current_f) if consecutive
        if(i >0 && current_a == prev_a +1){
            extend = (prev_end < current_f) ? prev_end : current_f;
        }
        else{
            extend =0;
        }
        int remaining = current_f - extend;
        g += remaining;
        int new_end;
        if(i >0 && current_a == prev_a +1){
            new_end = extend;
        }
        else{
            new_end =0;
        }
        prev_a = current_a;
        prev_end = new_end;
    }
    
    // Calculate floor(n / g)
    int ans = n / g;
    printf("%d\n", ans);
    
    // Free allocated memory
    free(a);
    free(unique_a);
    free(f);
    return 0;
}