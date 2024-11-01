#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 18
#define MAX_M 100000
#define MOD 998244353

int N, E, M;
int graph[MAX_N+1][MAX_N+1];
int dist[MAX_N+1][MAX_N+1];
long long inv[MAX_N+1];

void floyd_warshall() {
    for(int k = 1; k <= N; k++)
        for(int i = 1; i <= N; i++)
            for(int j = 1; j <= N; j++)
                if(dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
}

long long pow_mod(long long base, int exp) {
    long long result = 1;
    while(exp > 0) {
        if(exp & 1) result = (result * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return result;
}

void precompute_inv() {
    for(int i = 1; i <= N; i++)
        inv[i] = pow_mod(i, MOD-2);
}

int main() {
    scanf("%d %d", &N, &E);
    
    memset(graph, 0, sizeof(graph));
    for(int i = 1; i <= N; i++)
        for(int j = 1; j <= N; j++)
            dist[i][j] = (i == j) ? 0 : 1e9;
    
    for(int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = graph[v][u] = 1;
        dist[u][v] = dist[v][u] = 1;
    }
    
    floyd_warshall();
    precompute_inv();
    
    scanf("%d", &M);
    
    for(int day = 0; day < M; day++) {
        int n, s;
        scanf("%d", &n);
        
        int cities[MAX_N];
        for(int i = 0; i < n; i++)
            scanf("%d", &cities[i]);
        scanf("%d", &s);
        
        long long sum = 0;
        int max_dist = 0;
        
        for(int i = 0; i < n; i++) {
            int v = cities[i];
            if(dist[s][v] > max_dist)
                max_dist = dist[s][v];
        }
        
        for(int d = 1; d <= max_dist; d++) {
            long long ways = 0;
            for(int i = 0; i < n; i++) {
                int v = cities[i];
                if(dist[s][v] == d) ways++;
            }
            sum = (sum + ways * d * inv[n]) % MOD;
        }
        
        printf("%lld\n", sum);
    }
    
    return 0;
}