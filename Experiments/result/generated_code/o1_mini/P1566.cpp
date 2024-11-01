#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(const void *a, const void *b){
    return (*(int*)a - *(int*)b);
}

int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        int m;
        scanf("%d", &m);
        int arr[m];
        for(int i=0;i<m;i++) scanf("%d", &arr[i]);
        qsort(arr, m, sizeof(int), cmp);
        long long total = 0;
        for(int i=0;i<m;i++){
            int x = arr[i];
            int dp[x+1];
            memset(dp, 0, sizeof(dp));
            dp[0] = 1;
            for(int j=0;j<m;j++) {
                if(j == i) continue;
                int num = arr[j];
                if(num > x) continue;
                for(int s = x; s >= num; s--){
                    dp[s] += dp[s - num];
                }
            }
            total += dp[x];
        }
        printf("%lld\n", total);
    }
    return 0;
}