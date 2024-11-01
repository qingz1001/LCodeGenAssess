#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    int class_limit[k+1];
    for(int i=1;i<=k;i++) scanf("%d", &class_limit[i]);
    // Group items by class
    int **classes = (int **)malloc((k+1) * sizeof(int *));
    int *cnt = (int *)calloc(k+1, sizeof(int));
    for(int i=1;i<=k;i++) classes[i] = (int *)malloc((n+1) * sizeof(int));
    int a, b;
    for(int i=0;i<n;i++){
        scanf("%d %d", &a, &b);
        classes[b][cnt[b]++] = a;
    }
    // Initialize DP
    int dp[m+1];
    memset(dp, 0, sizeof(dp));
    // Process each class
    for(int c=1;c<=k;c++){
        // Temporary DP
        int tmp[m+1];
        memcpy(tmp, dp, sizeof(dp));
        for(int i=1;i<=cnt[c] && i<=class_limit[c];i++){
            for(int j=m; j>=i; j--){
                int sum = 0;
                for(int t=0;t<i;t++) sum += classes[c][t];
                if(j >= i && dp[j-i] + sum > tmp[j]){
                    tmp[j] = dp[j-i] + sum;
                }
            }
        }
        memcpy(dp, tmp, sizeof(dp));
    }
    // Find maximum
    int max = 0;
    for(int i=0;i<=m;i++) if(dp[i] > max) max = dp[i];
    printf("%d", max);
    // Free memory
    for(int i=1;i<=k;i++) free(classes[i]);
    free(classes);
    free(cnt);
    return 0;
}