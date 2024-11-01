#include <stdio.h>
#include <stdint.h>

#define MOD 100000000

int main(){
    int M, N;
    scanf("%d %d", &M, &N);
    int fert[M];
    for(int i=0;i<M;i++){
        fert[i]=0;
        for(int j=0;j<N;j++){
            int x;
            scanf("%d", &x);
            if(x) fert[i] |= (1<<j);
        }
    }
    int max_state = 1<<N;
    uint64_t dp_prev[max_state];
    uint64_t dp_curr[max_state];
    for(int s=0;s<max_state;s++) dp_prev[s]=0;
    dp_prev[0]=1;
    for(int row=0; row<M; row++){
        for(int s=0;s<max_state;s++) dp_curr[s]=0;
        for(int prev=0; prev<max_state; prev++) {
            if(dp_prev[prev]==0) continue;
            for(int s=0; s<max_state; s++){
                if( (s & ~fert[row]) !=0 ) continue;
                if( (s & (s>>1)) !=0 ) continue;
                if( (s & prev) !=0 ) continue;
                if( (s & (prev>>1)) !=0 ) continue;
                if( (s & (prev<<1)) !=0 ) continue;
                dp_curr[s] = (dp_curr[s] + dp_prev[prev]) % MOD;
            }
        }
        for(int s=0;s<max_state;s++) dp_prev[s]=dp_curr[s];
    }
    uint64_t result=0;
    for(int s=0;s<(1<<N);s++) result = (result + dp_prev[s]) % MOD;
    printf("%llu\n", result);
}