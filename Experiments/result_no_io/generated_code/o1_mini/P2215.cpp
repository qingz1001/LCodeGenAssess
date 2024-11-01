#include <stdio.h>
#include <stdlib.h>

#define MAXN 10005

typedef long long ll;

int cmp(const void* a, const void* b){
    if(*(int*)a < *(int*)b) return -1;
    if(*(int*)a > *(int*)b) return 1;
    return 0;
}

int main(){
    int N;
    scanf("%d", &N);
    int a[MAXN];
    for(int i=0;i<N;i++) scanf("%d", &a[i]);
    // Compute dp[i]: length of LIS starting at i
    int dp[MAXN];
    int tails[MAXN];
    int size =0;
    for(int i=N-1;i>=0;i--){
        int left=0, right=size;
        while(left < right){
            int mid = left + (right - left)/2;
            if(tails[mid] > a[i]) right = mid;
            else left = mid +1;
        }
        dp[i] = left +1;
        tails[left] = a[i];
        if(left == size) size++;
    }
    int M;
    scanf("%d", &M);
    while(M--){
        int L;
        scanf("%d", &L);
        if(L > size){
            printf("Impossible\n");
            continue;
        }
        int res[L];
        int pos =0;
        int last = -2147483648;
        int ok =1;
        for(int k=0;k<L;k++){
            int end = N - (L -k);
            int best = -1;
            int best_val = 2147483647;
            for(int j=pos; j<=end; j++){
                if(a[j] > last && dp[j] >= L -k){
                    if(a[j] < best_val){
                        best_val = a[j];
                        best = j;
                        if(best_val == -2147483648) break;
                    }
                }
            }
            if(best == -1){
                ok =0;
                break;
            }
            res[k] = a[best];
            last = a[best];
            pos = best +1;
        }
        if(ok){
            for(int k=0;k<L;k++) printf("%d%c", res[k], k<L-1?' ':'\n');
        }
        else{
            printf("Impossible\n");
        }
    }
    return 0;
}