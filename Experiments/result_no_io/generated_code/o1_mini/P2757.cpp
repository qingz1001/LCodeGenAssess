#include <stdio.h>
#include <stdlib.h>

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        int N;
        scanf("%d", &N);
        int *A = (int*)malloc((N+1)*sizeof(int));
        int *pos = (int*)malloc((N+1)*sizeof(int));
        for(int i=1;i<=N;i++){
            scanf("%d", &A[i]);
            pos[A[i]] = i;
        }
        int found=0;
        for(int j=1;j<=N && !found;j++){
            for(int i=1;i<j && !found;i++){
                int t = 2*A[j] - A[i];
                if(t >=1 && t <=N){
                    if(pos[t] > j){
                        found=1;
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