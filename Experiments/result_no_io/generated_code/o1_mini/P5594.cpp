#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    
    // Initialize counts for each day
    int *counts = (int*)calloc(k+1, sizeof(int));
    
    // Initialize flags for each day and each t
    // flags[d][t] = 1 if t is present on day d
    char **flags = (char**)malloc((k+1) * sizeof(char*));
    for(int d=0; d<=k; d++){
        flags[d] = (char*)calloc(m, sizeof(char));
    }
    
    // Read input and update counts
    for(int i=0; i<n; i++){
        for(int t=0; t<m; t++){
            int d;
            scanf("%d", &d);
            if(d >=1 && d <=k && t >=0 && t <m){
                if(flags[d][t] == 0){
                    counts[d]++;
                    flags[d][t] = 1;
                }
            }
        }
    }
    
    // Print counts from day 1 to day k
    for(int d=1; d<=k; d++){
        printf("%d", counts[d]);
        if(d != k) printf(" ");
    }
    printf("\n");
    
    // Free memory
    for(int d=0; d<=k; d++) free(flags[d]);
    free(flags);
    free(counts);
    
    return 0;
}