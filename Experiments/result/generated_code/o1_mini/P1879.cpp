#include <stdio.h>
#include <stdlib.h>

#define MOD 100000000

int main(){
    int M, N;
    scanf("%d %d", &M, &N);
    int row_fertile[M];
    for(int i=0;i<M;i++){
        row_fertile[i] = 0;
        for(int j=0; j<N; j++){
            int val;
            scanf("%d", &val);
            if(val){
                row_fertile[i] |= (1 << j);
            }
        }
    }
    int max_state = 1 << N;
    unsigned long long dp_prev[max_state];
    unsigned long long dp_curr[max_state];
    for(int s=0; s<max_state; s++) dp_prev[s] = 0;
    dp_prev[0] = 1;
    for(int i=0;i<M;i++){
        for(int s=0; s<max_state; s++) dp_curr[s] = 0;
        for(int prev=0; prev<max_state; prev++) {
            if(dp_prev[prev]==0) continue;
            for(int curr=0; curr<max_state; curr++){
                if( (curr & ~row_fertile[i]) !=0 ) continue;
                if( (curr & (curr >>1)) !=0 ) continue;
                if( (curr & prev)!=0 ) continue;
                dp_curr[curr] = (dp_curr[curr] + dp_prev[prev]) % MOD;
            }
        }
        for(int s=0; s<max_state; s++) dp_prev[s] = dp_curr[s];
    }
    unsigned long long result =0;
    for(int s=0; s<(1<<N); s++) {
        result = (result + dp_prev[s]) % MOD;
    }
    printf("%llu\n", result);
    return 0;
}