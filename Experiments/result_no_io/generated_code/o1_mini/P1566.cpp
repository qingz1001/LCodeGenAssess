#include <stdio.h>
#include <string.h>

#define MAX_M 30
#define MAX_X 1000
#define INF 31

int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        int m;
        scanf("%d", &m);
        int arr[MAX_M];
        for(int i=0;i<m;i++) scanf("%d", &arr[i]);
        int count=0;
        for(int i=0;i<m;i++){
            int x = arr[i];
            int dp[MAX_X+1];
            for(int j=0;j<=x;j++) dp[j]=INF;
            dp[0]=0;
            for(int j=0;j<m;j++){
                if(j == i) continue;
                int num = arr[j];
                if(num > x) continue;
                for(int k=x; k>=num; k--){
                    if(dp[k - num] + 1 < dp[k]){
                        dp[k] = dp[k - num] +1;
                    }
                }
            }
            if(dp[x] >=2 && dp[x] <=m-1){
                count++;
            }
        }
        printf("%d\n", count);
    }
    return 0;
}