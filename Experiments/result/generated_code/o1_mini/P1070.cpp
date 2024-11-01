#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAXN 1000
#define MAXM 1000
#define MAXP 1000
#define INF 100000000000LL

long long c[1001][1001];
int cost_arr[1001];
long long dp_prev[1001];
long long dp_cur[1001];

int main(){
    int n, m, p;
    scanf("%d %d %d", &n, &m, &p);

    // Read the coin counts
    for(int i=0; i<n; i++){
        for(int j=1; j<=m; j++){
            scanf("%lld", &c[i][j]);
        }
    }

    // Read the cost of robots
    for(int i=0; i<n; i++){
        scanf("%d", &cost_arr[i]);
    }

    // Initialize DP
    for(int i=0; i<=m; i++) dp_prev[i] = -INF;
    dp_prev[0] = 0;

    // Temporary arrays
    long long best_max;
    for(int l=1; l<=p; l++){
        for(int t=0; t + l <= m; t++){
            best_max = -INF;
            for(int s=0; s<n; s++){
                long long sum = 0;
                int road;
                int time;
                // Calculate sum for current s and l
                for(int k=0; k<l; k++){
                    road = (s + k) % n;
                    time = t + k +1;
                    sum += c[road][time];
                }
                long long temp = sum - (long long)cost_arr[s];
                if(temp > best_max){
                    best_max = temp;
                }
            }
            if(dp_prev[t] + best_max > dp_prev[t + l]){
                if(dp_prev[t + l] < dp_prev[t] + best_max){
                    dp_prev[t + l] = dp_prev[t] + best_max;
                }
            }
        }
    }

    // Now, iterate through possible robot placements
    // Reset dp_cur
    for(int i=0; i<=m; i++) dp_cur[i] = -INF;
    dp_cur[0] = 0;

    // Re-initialize dp_prev
    memcpy(dp_prev, dp_cur, sizeof(long long)*(m+1));

    for(int t=0; t<m; t++){
        if(dp_prev[t] == -INF) continue;
        int max_l = (p < m - t) ? p : (m - t);
        for(int l=1; l<=max_l; l++){
            long long current_max = -INF;
            for(int s=0; s<n; s++){
                long long sum = 0;
                int road;
                int time;
                for(int k=0; k<l; k++){
                    road = (s + k) % n;
                    time = t + k +1;
                    sum += c[road][time];
                }
                long long temp = sum - (long long)cost_arr[s];
                if(temp > current_max){
                    current_max = temp;
                }
            }
            if(dp_prev[t] + current_max > dp_prev[t + l]){
                dp_prev[t + l] = dp_prev[t] + current_max;
            }
        }
    }

    // Find the maximum value at dp[m]
    long long result = dp_prev[m];
    printf("%lld\n", result);
    return 0;
}