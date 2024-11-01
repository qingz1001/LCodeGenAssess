#include <stdio.h>
#include <string.h>
#define MOD 1000000009

typedef long long ll;

int main(){
    char S[500005];
    scanf("%s", S);
    int N = strlen(S);
    // 1-based indexing
    int b_run[N+2], w_run[N+2];
    ll q[N+2], pow2_pow[N+2];
    ll dp[N+2];
    // Initialize
    b_run[0] = w_run[0] =0;
    q[0] =0;
    dp[0] =1;
    pow2_pow[0] =1;
    for(int i=1;i<=N;i++){
        // Compute b_run
        if(S[i-1]=='B' || S[i-1]=='?'){
            b_run[i] = b_run[i-1] +1;
        }
        else{
            b_run[i] =0;
        }
        // Compute w_run
        if(S[i-1]=='W' || S[i-1]=='?'){
            w_run[i] = w_run[i-1] +1;
        }
        else{
            w_run[i] =0;
        }
        // Compute q
        q[i] = q[i-1] + (S[i-1]=='?' ? 1 : 0);
        // Compute pow2
        pow2_pow[i] = (pow2_pow[i-1] * 2) % MOD;
    }
    // Initialize dp
    for(int i=1;i<=N;i++) dp[i] =0;
    // Iterate over k
    for(int k=1; k<=N/2; k++){
        for(int i=2*k; i<=N; i++){
            int pos_b = i -k;
            if(b_run[pos_b] >=k && w_run[i] >=k){
                ll diff = q[i] - q[i -2*k];
                // Compute 2^diff modulo MOD
                ll val = 1;
                if(diff <= N){
                    val = pow2_pow[(int)diff];
                }
                else{
                    val = 0;
                }
                dp[i] = (dp[i] + (dp[i -2*k] * val) % MOD) % MOD;
            }
        }
    }
    printf("%lld\n", dp[N]);
}