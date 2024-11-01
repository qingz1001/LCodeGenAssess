#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int S_r, S_b, S_g, m, P;
    scanf("%d %d %d %d %d", &S_r, &S_b, &S_g, &m, &P);
    int n = S_r + S_b + S_g;
    int parent[n+1];
    for(int i=1;i<=n;i++) parent[i]=i;
    // Union-Find functions
    int find_set(int x){
        if(parent[x]!=x){
            parent[x]=find_set(parent[x]);
        }
        return parent[x];
    }
    // Read and process shuffles
    int *perm = (int*)malloc((n+1)*sizeof(int));
    for(int i=0;i<m;i++){
        for(int j=1;j<=n;j++) scanf("%d", &perm[j]);
        for(int j=1;j<=n;j++) {
            int a = find_set(j);
            int b = find_set(perm[j]);
            if(a != b){
                parent[a] = b;
            }
        }
    }
    // Collect orbit sizes
    int orbit_size[61];
    memset(orbit_size, 0, sizeof(orbit_size));
    for(int i=1;i<=n;i++) {
        int rep = find_set(i);
        orbit_size[rep]++;
    }
    int sizes[61];
    int t=0;
    for(int i=1;i<=n;i++) if(orbit_size[i]>0) sizes[t++] = orbit_size[i];
    // DP
    int dp[21][21];
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    for(int i=0;i<t;i++){
        int c = sizes[i];
        int dp2[21][21];
        memset(dp2, 0, sizeof(dp2));
        for(int a=0;a<=S_r;a++) {
            for(int b=0;b<=S_b;b++) {
                if(dp[a][b]){
                    // Assign to red
                    if(a + c <= S_r){
                        dp2[a + c][b] = (dp2[a + c][b] + dp[a][b]) % P;
                    }
                    // Assign to blue
                    if(b + c <= S_b){
                        dp2[a][b + c] = (dp2[a][b + c] + dp[a][b]) % P;
                    }
                    // Assign to green
                    dp2[a][b] = (dp2[a][b] + dp[a][b]) % P;
                }
            }
        }
        // Update dp
        for(int a=0;a<=S_r;a++) {
            for(int b=0;b<=S_b;b++) {
                dp[a][b] = dp2[a][b];
            }
        }
    }
    printf("%d\n", dp[S_r][S_b]);
    free(perm);
    return 0;
}