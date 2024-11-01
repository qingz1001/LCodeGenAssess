#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long R, C, A, B;
long long grid[505][505];
long long prefix[505][505];

int feasible(long long K) {
    long long horizontal = 0;
    long long acc[505];
    memset(acc, 0, sizeof(acc));
    for(long long r = 1; r <= R; r++) {
        for(long long c = 1; c <= C; c++) {
            acc[c] += grid[r][c];
        }
        // Try to split columns
        long long splits = 0;
        long long temp = 0;
        for(long long c = 1; c <= C; c++) {
            temp += acc[c];
            if(temp >= K) {
                splits++;
                temp = 0;
            }
        }
        if(splits >= B) {
            horizontal++;
            memset(acc, 0, sizeof(acc));
            if(horizontal == A) break;
        }
    }
    return horizontal >= A;
}

int main(){
    scanf("%lld %lld %lld %lld", &R, &C, &A, &B);
    for(long long r =1;r<=R;r++) {
        for(long long c=1;c<=C;c++) {
            scanf("%lld", &grid[r][c]);
        }
    }
    long long left = 0, right = 4000LL*500*500;
    while(left < right){
        long long mid = left + (right - left +1)/2;
        if(feasible(mid)) left = mid;
        else right = mid-1;
    }
    printf("%lld\n", left);
}