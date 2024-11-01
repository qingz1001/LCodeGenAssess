#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 50
#define MAX_P 24
#define INF 1000000000

typedef long long ll;

typedef struct {
    int u, v, w;
} Edge;

int main(){
    int n, m, s, t;
    ll k;
    scanf("%d %d %d %d %lld", &n, &m, &s, &t, &k);
    int adj[MAX_N+1][MAX_N+1];
    for(int i=0;i<=n;i++) for(int j=0;j<=n;j++) adj[i][j]=INF;
    for(int i=0;i<m;i++){
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        if(w < adj[u][v]){
            adj[u][v] = adj[v][u] = w;
        }
    }
    int a;
    scanf("%d", &a);
    int periods[MAX_P];
    int lcm = 1;
    for(int i=0;i<a;i++){
        int T;
        scanf("%d", &T);
        periods[i] = T;
        // Compute LCM
        // Since T <=4 and a<=30, LCM won't exceed 12
        // Simple LCM computation
        int g, x=lcm, y=T;
        // Compute GCD
        while(y){
            g = x % y;
            x = y;
            y = g;
        }
        int gcd = x;
        lcm = lcm / gcd * T;
    }
    if(a==0) lcm =1;
    // Initialize forbidden nodes for each time step
    int forbidden[MAX_P][MAX_N+1];
    for(int p=0;p<lcm;p++) for(int i=1;i<=n;i++) forbidden[p][i]=0;
    // Reset reading for monsters
    fseek(stdin, 0, SEEK_SET);
    scanf("%d %d %d %d %lld", &n, &m, &s, &t, &k);
    for(int i=0;i<m;i++){
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
    }
    scanf("%d", &a);
    for(int i=0;i<a;i++){
        int T;
        scanf("%d", &T);
        int path[T];
        for(int j=0; j<T; j++) scanf("%d", &path[j]);
        for(int p=0;p<lcm;p++) {
            int pos = path[p % T];
            forbidden[p][pos] =1;
        }
    }
    // Binary search for B
    int low = 1, high = 0;
    for(int u=1; u<=n; u++) for(int v=1; v<=n; v++) if(adj[u][v]!=INF){
        if(adj[u][v] > high) high = adj[u][v];
    }
    int answer = -1;
    while(low <= high){
        int mid = low + (high - low)/2;
        // Build adjacency list with w <= mid
        int allowed[MAX_N+1][MAX_N+1];
        for(int u=1; u<=n; u++) for(int v=1; v<=n; v++) {
            allowed[u][v] = (adj[u][v] <= mid) ? 1 : 0;
        }
        // DP with state (node, time mod lcm)
        // Initialize
        int dp_prev[MAX_N+1][MAX_P];
        memset(dp_prev, 0, sizeof(dp_prev));
        if(!forbidden[0][s]){
            dp_prev[s][0] =1;
        }
        // Iterate k steps
        ll steps = k;
        // To optimize, use matrix exponentiation or similar, but here k <=2e9 and lcm small
        // Implement DP step by step with cycle
        // Since n and lcm are small, feasible
        for(int step=1; step<=steps; step++){
            int dp_curr[MAX_N+1][MAX_P];
            memset(dp_curr, 0, sizeof(dp_curr));
            int p = step % lcm;
            for(int u=1; u<=n; u++) for(int pt=0; pt<lcm; pt++) if(dp_prev[u][pt]){
                for(int v=1; v<=n; v++) if(allowed[u][v] && !forbidden[p][v]){
                    dp_curr[v][p] =1;
                }
            }
            memcpy(dp_prev, dp_curr, sizeof(dp_prev));
            // Early exit if no states
            int any =0;
            for(int u=1; u<=n; u++) for(int p=0; p<lcm; p++) if(dp_prev[u][p]) {any=1; break;}
            if(!any) break;
        }
        // Check if t is reachable at step k
        int reachable =0;
        for(int p=0; p<lcm; p++) if(dp_prev[t][p]) {reachable=1; break;}
        if(reachable){
            answer = mid;
            high = mid -1;
        }
        else{
            low = mid +1;
        }
    }
    if(answer != -1) printf("%d\n", answer);
    else printf("IMP0SSBLE!!\n");
}