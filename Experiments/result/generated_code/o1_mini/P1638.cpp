#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    
    int *a = (int*)malloc((n + 1) * sizeof(int));
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    
    int *counts = (int*)calloc(m + 1, sizeof(int));
    int distinct = 0;
    int best_l = 1, best_r = n;
    int min_len = n;
    int l = 1;
    
    for(int r = 1; r <= n; r++){
        if(counts[a[r]] == 0){
            distinct++;
        }
        counts[a[r]]++;
        
        while(distinct == m){
            if((r - l + 1) < min_len){
                min_len = r - l + 1;
                best_l = l;
                best_r = r;
            }
            counts[a[l]]--;
            if(counts[a[l]] == 0){
                distinct--;
            }
            l++;
        }
    }
    
    printf("%d %d\n", best_l, best_r);
    
    free(a);
    free(counts);
    return 0;
}