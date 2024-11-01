#include <stdio.h>
#include <stdlib.h>

long long L;
int N, M;
long long positions[50002]; // 0 to N+1

int is_possible(long long d) {
    int removed = 0;
    int last = 0;
    for(int i = 1; i < N+2; i++) {
        if(positions[i] - positions[last] < d){
            removed++;
            if(removed > M) return 0;
        }
        else{
            last = i;
        }
    }
    return 1;
}

int main(){
    scanf("%lld %d %d", &L, &N, &M);
    positions[0] = 0;
    for(int i = 1; i <= N; i++) {
        scanf("%lld", &positions[i]);
    }
    positions[N+1] = L;
    
    long long low = 1, high = L, result = 0;
    while(low <= high){
        long long mid = low + (high - low) / 2;
        if(is_possible(mid)){
            result = mid;
            low = mid + 1;
        }
        else{
            high = mid - 1;
        }
    }
    printf("%lld", result);
    return 0;
}