#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int cmp(const void *a, const void *b){
    int ia = *(int*)a;
    int ib = *(int*)b;
    if(ia < ib) return -1;
    if(ia > ib) return 1;
    return 0;
}

int main(){
    long long L;
    int S, T, M;
    scanf("%lld", &L);
    scanf("%d %d %d", &S, &T, &M);
    int stones[102];
    stones[0] = 0;
    for(int i=1;i<=M;i++) scanf("%d", &stones[i]);
    qsort(stones+1, M, sizeof(int), cmp);
    stones[M+1] = (int)L;
    int total = M+2;
    long long dp[102];
    for(int i=0;i<total;i++) dp[i] = LONG_LONG_MAX;
    dp[0] = 0;
    for(int i=0;i<M+1;i++){
        if(dp[i] == LONG_LONG_MAX) continue;
        for(int j=i+1;j<total;j++){
            long long dist = stones[j] - stones[i];
            if(dist < S || dist > T) continue;
            long long cost = dp[i] + (j <= M ? 1 : 0);
            if(cost < dp[j]) dp[j] = cost;
        }
    }
    printf("%lld\n", dp[M+1]);
    return 0;
}