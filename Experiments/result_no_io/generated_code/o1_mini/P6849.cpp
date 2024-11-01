#include <stdio.h>
#include <stdlib.h>

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    
    int *a = (int*)malloc((N+1) * sizeof(int));
    for(int i=1;i<=N;i++) scanf("%d", &a[i]);
    
    int *b = (int*)malloc((M+1) * sizeof(int));
    for(int j=1;j<=M;j++) scanf("%d", &b[j]);
    
    // Allocate w as a 1D array
    long long *w = (long long*)malloc((long long)N * M * sizeof(long long));
    for(int i=0;i<N;i++) {
        for(int j=0;j<M;j++) {
            scanf("%lld", &w[i*M + j]);
        }
    }
    
    int *assignment = (int*)malloc((N+1) * sizeof(int));
    for(int i=1;i<=N;i++) assignment[i] = 0;
    
    for(int i=1;i<=N;i++){
        long long max_w = -1;
        int chosen_j = 0;
        for(int j=1;j<=M;j++){
            if(b[j] >= a[i]){
                long long current_w = w[(i-1)*M + (j-1)];
                if(current_w > max_w){
                    max_w = current_w;
                    chosen_j = j;
                }
            }
        }
        if(chosen_j != 0){
            assignment[i] = chosen_j;
            b[chosen_j] -= a[i];
        }
    }
    
    for(int i=1;i<=N;i++) printf("%d\n", assignment[i]);
    
    free(a);
    free(b);
    free(w);
    free(assignment);
    return 0;
}