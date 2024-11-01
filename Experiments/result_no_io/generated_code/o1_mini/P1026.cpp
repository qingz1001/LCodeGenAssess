#include <stdio.h>
#include <string.h>

#define MAX_N 200
#define MAX_K 40
#define MAX_S 6
#define MAX_WORD_LEN 20

int main(){
    int p, k;
    while(scanf("%d %d", &p, &k)!=EOF){
        char S[MAX_N +1];
        S[0] = '\0';
        for(int i=0;i<p;i++){
            char line[21];
            scanf("%s", line);
            strcat(S, line);
        }
        int N = strlen(S);
        int s;
        scanf("%d", &s);
        char words[MAX_S][MAX_WORD_LEN +1];
        for(int i=0;i<s;i++) scanf("%s", words[i]);
        // Precompute has_word
        int has_word[MAX_N];
        for(int i=0;i<N;i++) has_word[i] = 0;
        for(int i=0;i<N;i++){
            for(int j=0;j<s;j++){
                int len = strlen(words[j]);
                if(i + len <= N && strncmp(&S[i], words[j], len)==0){
                    has_word[i] = 1;
                    break;
                }
            }
        }
        // Compute prefix sums
        int sum[MAX_N +1];
        sum[0] = 0;
        for(int i=0;i<N;i++) sum[i+1] = sum[i] + has_word[i];
        // Initialize DP
        // dp[k][pos]
        int dp[MAX_K +1][MAX_N +1];
        for(int i=0;i<=k;i++) {
            for(int j=0;j<=N;j++) {
                dp[i][j] = -1;
            }
        }
        // Base case: k=1
        for(int pos=0; pos<N; pos++) {
            dp[1][pos] = sum[N] - sum[pos];
        }
        // Fill DP
        for(int current_k=2; current_k<=k; current_k++){
            for(int pos=0; pos<N; pos++){
                if(N - pos < current_k) continue;
                int max_val = -1;
                for(int q=pos+1; q<=N - (current_k -1); q++){
                    if(dp[current_k -1][q] == -1) continue;
                    int current = (sum[q] - sum[pos]) + dp[current_k -1][q];
                    if(current > max_val){
                        max_val = current;
                    }
                }
                dp[current_k][pos] = max_val;
            }
        }
        // The answer is dp[k][0]
        printf("%d\n", dp[k][0]);
    }
    return 0;
}