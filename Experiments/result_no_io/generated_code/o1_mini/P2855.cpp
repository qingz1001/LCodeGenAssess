#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort
int cmp(const void *a, const void *b) {
    long long aa = *(long long*)a;
    long long bb = *(long long*)b;
    if (aa < bb) return -1;
    else if (aa > bb) return 1;
    else return 0;
}

int main(){
    long long L;
    int N, M;
    scanf("%lld %d %d", &L, &N, &M);
    
    // Allocate N+2 positions
    long long *pos = (long long*)malloc((N + 2) * sizeof(long long));
    pos[0] = 0;
    for(int i=1;i<=N;i++) {
        scanf("%lld", &pos[i]);
    }
    pos[N+1] = L;
    
    // Sort the positions
    qsort(pos, N+2, sizeof(long long), cmp);
    
    // Binary search
    long long left = 1, right = L, answer = 0;
    while(left <= right){
        long long mid = left + (right - left) / 2;
        int removed = 0;
        long long last = pos[0];
        for(int i=1;i<N+2;i++){
            if(pos[i] - last < mid){
                removed++;
            }
            else{
                last = pos[i];
            }
        }
        if(removed <= M){
            answer = mid;
            left = mid +1;
        }
        else{
            right = mid -1;
        }
    }
    
    printf("%lld\n", answer);
    free(pos);
    return 0;
}