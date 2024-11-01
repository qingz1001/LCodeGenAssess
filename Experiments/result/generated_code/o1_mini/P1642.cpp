#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 101
#define INF 1e18

int N, M;
int w[MAXN], c_val[MAXN];
int adj[MAXN][MAXN];
int adj_size[MAXN];
double dp_val[MAXN][MAXN];
int K;

void compute_dp(int u, int parent, double X) {
    // Initialize dp[u][1]
    for(int i=1;i<=K;i++) {
        dp_val[u][i] = -INF;
    }
    dp_val[u][1] = w[u] - X * c_val[u];
    
    for(int i=0;i<adj_size[u];i++) {
        int v = adj[u][i];
        if(v == parent) continue;
        compute_dp(v, u, X);
        
        double tmp[MAXN];
        for(int j=0; j<=K; j++) {
            tmp[j] = -INF;
        }
        
        for(int size_u_now=1; size_u_now<=K; size_u_now++) {
            if(dp_val[u][size_u_now] < -1e17) continue;
            for(int size_v_now=1; size_v_now<=K - size_u_now; size_v_now++) {
                if(dp_val[v][size_v_now] < -1e17) continue;
                if(tmp[size_u_now + size_v_now] < dp_val[u][size_u_now] + dp_val[v][size_v_now]) {
                    tmp[size_u_now + size_v_now] = dp_val[u][size_u_now] + dp_val[v][size_v_now];
                }
            }
        }
        
        for(int j=1; j<=K; j++) {
            if(tmp[j] > dp_val[u][j]) {
                dp_val[u][j] = tmp[j];
            }
        }
    }
}

int check(double X) {
    K = N - M;
    for(int root=1; root<=N; root++) {
        // Initialize dp_val
        for(int i=1;i<=N;i++) {
            for(int j=0;j<=K;j++) {
                dp_val[i][j] = -INF;
            }
        }
        compute_dp(root, -1, X);
        if(dp_val[root][K] >= -1e-6) {
            return 1;
        }
    }
    return 0;
}

int main(){
    scanf("%d %d", &N, &M);
    for(int i=1;i<=N;i++) {
        scanf("%d", &w[i]);
    }
    for(int i=1;i<=N;i++) {
        scanf("%d", &c_val[i]);
    }
    for(int i=0;i<N-1;i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        adj[a][adj_size[a]++] = b;
        adj[b][adj_size[b]++] = a;
    }
    
    double low = 0.0, high = 100000.0;
    for(int it=0; it<100; it++) {
        double mid = (low + high) / 2.0;
        if(check(mid)){
            low = mid;
        }
        else{
            high = mid;
        }
    }
    
    printf("%.1lf\n", low);
    return 0;
}