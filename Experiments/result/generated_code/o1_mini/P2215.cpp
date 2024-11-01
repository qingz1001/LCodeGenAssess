#include <stdio.h>
#include <stdlib.h>

int main(){
    int N;
    if(scanf("%d", &N)!=1){
        return 0;
    }
    int *a = (int*)malloc(sizeof(int)*N);
    for(int i=0;i<N;i++) scanf("%d", &a[i]);
    int M;
    if(scanf("%d", &M)!=1){
        free(a);
        return 0;
    }
    while(M--){
        int L;
        if(scanf("%d", &L)!=1){
            break;
        }
        if(L > N){
            printf("Impossible\n");
            continue;
        }
        int res[L];
        int pos = 0;
        int last = -2147483648; // Initialize to minimum integer
        int found = 1;
        for(int step=0; step<L; step++){
            int start = pos;
            int end = N - (L - step);
            int selected = -1;
            for(int j=start; j<=end; j++){
                if(a[j] > last){
                    selected = j;
                    last = a[j];
                    pos = j +1;
                    res[step] = a[j];
                    break;
                }
            }
            if(selected == -1){
                found = 0;
                break;
            }
        }
        if(found){
            for(int i=0;i<L;i++){
                if(i>0) printf(" ");
                printf("%d", res[i]);
            }
            printf("\n");
        }
        else{
            printf("Impossible\n");
        }
    }
    free(a);
    return 0;
}