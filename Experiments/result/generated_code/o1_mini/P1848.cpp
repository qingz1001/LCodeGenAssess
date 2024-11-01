#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

// Binary search to find the first index where S[idx] >= target
int lower_bound_search(ll *S, int start, int end, ll target) {
    int l = start;
    int r = end;
    int res = end + 1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (S[m] >= target) {
            res = m;
            r = m - 1;
        }
        else {
            l = m + 1;
        }
    }
    return res;
}

int main(){
    int N;
    ll L;
    scanf("%d %lld", &N, &L);
    int *H = (int*)malloc((N+1) * sizeof(int));
    int *W = (int*)malloc((N+1) * sizeof(int));
    for(int i=1;i<=N;i++) {
        scanf("%d %d", &H[i], &W[i]);
    }
    ll *S = (ll*)malloc((N+1) * sizeof(ll));
    S[0] = 0;
    for(int i=1;i<=N;i++) {
        S[i] = S[i-1] + W[i];
    }
    ll *DP = (ll*)malloc((N+1) * sizeof(ll));
    DP[0] = 0;
    for(int i=1;i<=N;i++) {
        ll target = S[i] - L;
        int j_min;
        if(target <= 0){
            j_min = 1;
        }
        else{
            j_min = lower_bound_search(S, 0, i-1, target) + 1;
            if(j_min < 1) j_min = 1;
        }
        DP[i] = 1e18;
        int maxH = 0;
        for(int j=i; j>=j_min; j--){
            // Early break if the width exceeds L
            if(S[i] - S[j-1] > L) break;
            if(H[j] > maxH){
                maxH = H[j];
                if(DP[j-1] + maxH < DP[i]){
                    DP[i] = DP[j-1] + maxH;
                }
            }
        }
    }
    printf("%lld\n", DP[N]);
    free(H);
    free(W);
    free(S);
    free(DP);
    return 0;
}