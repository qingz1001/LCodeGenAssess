#include <stdio.h>
#include <stdlib.h>

#define MAX_N 500000

int main(){
    int T;
    if(scanf("%d", &T)!=1) return 0;
    while(T--){
        int N;
        if(scanf("%d", &N)!=1) return 0;
        // Allocate memory for pos
        // Using VLA for simplicity, assuming N <=500,000
        int *A = (int*)malloc((N+1)*sizeof(int));
        int *pos = (int*)malloc((N+1)*sizeof(int));
        for(int i=1;i<=N;i++){
            if(scanf("%d", &A[i])!=1){
                free(A);
                free(pos);
                return 0;
            }
            pos[A[i]] = i;
        }
        int found = 0;
        for(int b=1; b<=N && !found; b++){
            // c ranges from b+1 to min(2*b-1, N)
            int c_start = b+1;
            int c_end = 2*b -1;
            if(c_end > N) c_end = N;
            for(int c = c_start; c <= c_end && !found; c++){
                int a = 2*b -c;
                if(a >=1 && a < b){
                    if(pos[a] < pos[b] && pos[b] < pos[c]){
                        found =1;
                    }
                }
            }
        }
        if(found) printf("Y\n");
        else printf("N\n");
        free(A);
        free(pos);
    }
    return 0;
}