#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n;
long long p;
int S;
int *W;
long long *V;

int max(int a, int b){
    return a > b ? a : b;
}

int main(){
    scanf("%d %lld %d", &n, &p, &S);
    W = (int*)malloc(n * sizeof(int));
    V = (long long*)malloc(n * sizeof(long long));
    int maxW = 0;
    for(int i=0;i<n;i++){
        scanf("%d %lld", &W[i], &V[i]);
        if(W[i] > maxW) maxW = W[i];
    }
    int left = 1, right = maxW, answer = -1;
    int *dp = (int*)malloc((S+1) * sizeof(int));
    while(left <= right){
        int mid = left + (right - left) / 2;
        memset(dp, -1, (S+1)*sizeof(int));
        dp[0] = 0;
        for(int i=0;i<n;i++){
            if(W[i] > mid) continue;
            for(int j=S; j>=W[i]; j--){
                if(dp[j - W[i]] != -1){
                    long long temp = (long long)dp[j - W[i]] + V[i];
                    if(temp > dp[j]) dp[j] = temp;
                }
            }
        }
        long long res = 0;
        for(int j=0;j<=S;j++) if(dp[j] > res) res = dp[j];
        if(res >= p){
            answer = mid;
            right = mid - 1;
        }
        else{
            left = mid + 1;
        }
    }
    if(answer != -1) printf("%d\n", answer);
    else printf("No Solution!\n");
    free(W);
    free(V);
    free(dp);
    return 0;
}