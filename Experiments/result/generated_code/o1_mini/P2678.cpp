#include <stdio.h>
#include <stdlib.h>

int main(){
    int L, N, M;
    scanf("%d %d %d", &L, &N, &M);
    // Allocate array with N+2 elements (start and end)
    int *D = (int*) malloc((N + 2) * sizeof(int));
    D[0] = 0;
    for(int i=1;i<=N;i++) {
        scanf("%d", &D[i]);
    }
    D[N+1] = L;
    // Binary search
    int low = 1, high = L, answer = 0;
    while(low <= high){
        int mid = low + (high - low)/2;
        int removed = 0;
        int last = 0;
        for(int i=1;i<=N+1;i++){
            if(D[i] - D[last] < mid){
                removed++;
            }
            else{
                last = i;
            }
        }
        if(removed <= M){
            answer = mid;
            low = mid +1;
        }
        else{
            high = mid -1;
        }
    }
    printf("%d\n", answer);
    free(D);
    return 0;
}