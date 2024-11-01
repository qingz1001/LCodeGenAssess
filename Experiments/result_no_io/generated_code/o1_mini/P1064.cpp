#include <stdio.h>
#include <string.h>

typedef struct {
    int v;
    int p;
} Item;

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    n /= 10;
    Item mainItems[60];
    Item attach1[60];
    Item attach2[60];
    memset(mainItems, 0, sizeof(mainItems));
    memset(attach1, 0, sizeof(attach1));
    memset(attach2, 0, sizeof(attach2));
    int mainCount = 0;
    for(int i=0;i<m;i++){
        int v, p, q;
        scanf("%d %d %d", &v, &p, &q);
        v /=10;
        if(q ==0){
            mainItems[mainCount].v = v;
            mainItems[mainCount].p = p;
            mainCount++;
        }
        else{
            if(attach1[q-1].v ==0){
                attach1[q-1].v = v;
                attach1[q-1].p = p;
            }
            else{
                attach2[q-1].v = v;
                attach2[q-1].p = p;
            }
        }
    }
    int dp[3201];
    memset(dp, 0, sizeof(dp));
    for(int i=0;i<mainCount;i++){
        for(int j=n; j>=0; j--){
            if(mainItems[i].v <= j){
                if(dp[j] < dp[j - mainItems[i].v] + mainItems[i].v * mainItems[i].p){
                    dp[j] = dp[j - mainItems[i].v] + mainItems[i].v * mainItems[i].p;
                }
                if(attach1[i].v !=0 && mainItems[i].v + attach1[i].v <=j){
                    if(dp[j] < dp[j - mainItems[i].v - attach1[i].v] + mainItems[i].v * mainItems[i].p + attach1[i].v * attach1[i].p){
                        dp[j] = dp[j - mainItems[i].v - attach1[i].v] + mainItems[i].v * mainItems[i].p + attach1[i].v * attach1[i].p;
                    }
                }
                if(attach2[i].v !=0 && mainItems[i].v + attach2[i].v <=j){
                    if(dp[j] < dp[j - mainItems[i].v - attach2[i].v] + mainItems[i].v * mainItems[i].p + attach2[i].v * attach2[i].p){
                        dp[j] = dp[j - mainItems[i].v - attach2[i].v] + mainItems[i].v * mainItems[i].p + attach2[i].v * attach2[i].p;
                    }
                }
                if(attach1[i].v !=0 && attach2[i].v !=0 && mainItems[i].v + attach1[i].v + attach2[i].v <=j){
                    if(dp[j] < dp[j - mainItems[i].v - attach1[i].v - attach2[i].v] + mainItems[i].v * mainItems[i].p + attach1[i].v * attach1[i].p + attach2[i].v * attach2[i].p){
                        dp[j] = dp[j - mainItems[i].v - attach1[i].v - attach2[i].v] + mainItems[i].v * mainItems[i].p + attach1[i].v * attach1[i].p + attach2[i].v * attach2[i].p;
                    }
                }
            }
        }
    }
    int res =0;
    for(int i=0;i<=n;i++) if(dp[i] > res) res = dp[i];
    printf("%d", res*10);
    return 0;
}