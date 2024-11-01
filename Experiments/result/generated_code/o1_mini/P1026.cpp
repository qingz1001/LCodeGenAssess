#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 200
#define MAX_K 40
#define MAX_S 6
#define MAX_WORD_LEN 6

int main(){
    int p, k;
    while(scanf("%d %d", &p, &k)!=EOF){
        char S[MAX_N+1];
        S[0] = '\0';
        char buffer[25];
        for(int i=0;i<p;i++){
            scanf("%s", buffer);
            strncat(S, buffer, MAX_N - strlen(S));
        }
        int N = strlen(S);
        int s;
        scanf("%d", &s);
        char words[MAX_S][MAX_WORD_LEN+1];
        for(int i=0;i<s;i++) scanf("%s", words[i]);
        int match[MAX_N];
        for(int i=0;i<N;i++) match[i]=0;
        for(int i=0;i<N;i++){
            for(int w=0; w<s; w++){
                int len = strlen(words[w]);
                if(i + len <= N && strncmp(S+i, words[w], len)==0){
                    match[i]=1;
                    break;
                }
            }
        }
        int sum[MAX_N+1];
        sum[0]=0;
        for(int i=0;i<N;i++) sum[i+1] = sum[i] + match[i];
        // Initialize DP
        int dp[MAX_N+1][MAX_K+1];
        for(int i=0;i<=N;i++) {
            for(int j=0;j<=k;j++) dp[i][j]=-1;
        }
        dp[0][0]=0;
        for(int j_pos=0; j_pos<N; j_pos++){
            for(int m=0; m<k; m++){
                if(dp[j_pos][m]==-1) continue;
                for(int t=j_pos+1; t<=N; t++){
                    if(m+1 >k) break;
                    int current = dp[j_pos][m] + (sum[t] - sum[j_pos]);
                    if(current > dp[t][m+1]){
                        dp[t][m+1] = current;
                    }
                }
            }
        }
        if(dp[N][k]==-1) printf("0\n");
        else printf("%d\n", dp[N][k]);
    }
    return 0;
}