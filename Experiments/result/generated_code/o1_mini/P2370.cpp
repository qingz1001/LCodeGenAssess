#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

int main(){
    int n;
    ll p;
    int S;
    scanf("%d %lld %d", &n, &p, &S);
    
    int W[1001];
    ll V[1001];
    int W_max = 0;
    for(int i=0;i<n;i++){
        scanf("%d %lld", &W[i], &V[i]);
        if(W[i] > W_max) W_max = W[i];
    }
    
    int lower = 1, upper = W_max, answer = -1;
    ll dp[1001];
    
    while(lower <= upper){
        int mid = lower + (upper - lower) / 2;
        memset(dp, -1, sizeof(dp));
        dp[0] = 0;
        
        for(int i=0;i<n;i++){
            if(W[i] > mid) continue;
            for(int s = S; s >= W[i]; s--){
                if(dp[s - W[i]] != -1){
                    if(dp[s] < dp[s - W[i]] + V[i]){
                        dp[s] = dp[s - W[i]] + V[i];
                    }
                }
            }
        }
        
        ll max_val = 0;
        for(int s=0;s<=S;s++) {
            if(dp[s] > max_val){
                max_val = dp[s];
            }
        }
        
        if(max_val >= p){
            answer = mid;
            upper = mid -1;
        }
        else{
            lower = mid +1;
        }
    }
    
    if(answer == -1){
        printf("No Solution!\n");
    }
    else{
        printf("%d\n", answer);
    }
}