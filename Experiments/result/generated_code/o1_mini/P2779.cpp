#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef long long ll;

const int MOD = 1000000009;

int main(){
    char S[500005];
    scanf("%s", S);
    int L = strlen(S);
    // 1-based indexing
    int *pre_q = (int*)calloc(L+2, sizeof(int));
    int *preB = (int*)calloc(L+2, sizeof(int));
    int *preW = (int*)calloc(L+2, sizeof(int));
    int *cntB = (int*)calloc(L+2, sizeof(int));
    int *cntW = (int*)calloc(L+2, sizeof(int));
    ll *power2 = (ll*)calloc(L*2+2, sizeof(ll)); // to prevent overflow in q1+q2
    ll *dp = (ll*)calloc(L+2, sizeof(ll));
    // Compute cntB and cntW
    cntB[L] = (S[L-1] == 'B' || S[L-1] == '?') ? 1 : 0;
    cntW[L] = (S[L-1] == 'W' || S[L-1] == '?') ? 1 : 0;
    for(int i = L-1; i >=0; i--){
        if(S[i] == 'B' || S[i] == '?'){
            cntB[i+1] = cntB[i+2] +1;
        }
        else{
            cntB[i+1] =0;
        }
        if(S[i] == 'W' || S[i] == '?'){
            cntW[i+1] = cntW[i+2] +1;
        }
        else{
            cntW[i+1] =0;
        }
    }
    // Compute pre_q, preB, preW
    pre_q[0] =0;
    preB[0] =0;
    preW[0] =0;
    for(int i=1;i<=L;i++){
        pre_q[i] = pre_q[i-1] + (S[i-1] == '?');
        preB[i] = preB[i-1] + ((S[i-1] == 'B') || (S[i-1] == '?'));
        preW[i] = preW[i-1] + ((S[i-1] == 'W') || (S[i-1] == '?'));
    }
    // Compute power2
    power2[0] =1;
    for(int i=1;i<=L*2;i++){
        power2[i] = (power2[i-1] * 2) % MOD;
    }
    // Initialize dp
    dp[0] =1;
    // Iterate over k
    for(int k=1; k<=L/2; k++){
        int max_x = L - 2*k +1;
        for(int x=1; x<=max_x; x++){
            if(cntB[x] >=k && cntW[x +k] >=k){
                int i = x + 2*k -1;
                int q1 = pre_q[x +k -1] - pre_q[x-1];
                int q2 = pre_q[i] - pre_q[x +k -1];
                if(q1 + q2 > L*2){
                    // To prevent overflow, but in practice q1+q2 <= L
                    q1 = L*2;
                    q2 =0;
                }
                ll ways = power2[q1 + q2];
                dp[i] = (dp[i] + (dp[x-1] * ways) % MOD) % MOD;
            }
        }
    }
    printf("%lld\n", dp[L]%MOD);
    free(pre_q);
    free(preB);
    free(preW);
    free(cntB);
    free(cntW);
    free(power2);
    free(dp);
    return 0;
}