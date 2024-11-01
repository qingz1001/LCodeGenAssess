#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 19
#define MAXM 100001
#define MOD 998244353

int N, E, M;
int graph[MAXN][MAXN];
int depth[MAXN];
int q[MAXN], front, rear;

long long pow_mod(long long base, int exp) {
    long long result = 1;
    while (exp > 0) {
        if (exp & 1) result = result * base % MOD;
        base = base * base % MOD;
        exp >>= 1;
    }
    return result;
}

void bfs(int start) {
    memset(depth, -1, sizeof(depth));
    front = rear = 0;
    q[rear++] = start;
    depth[start] = 0;

    while (front < rear) {
        int cur = q[front++];
        for (int i = 1; i <= N; i++) {
            if (graph[cur][i] && depth[i] == -1) {
                depth[i] = depth[cur] + 1;
                q[rear++] = i;
            }
        }
    }
}

int main() {
    scanf("%d %d", &N, &E);
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = graph[v][u] = 1;
    }

    scanf("%d", &M);
    for (int i = 0; i < M; i++) {
        int n, s;
        scanf("%d", &n);
        int max_depth = 0;
        for (int j = 0; j < n; j++) {
            int c;
            scanf("%d", &c);
        }
        scanf("%d", &s);

        bfs(s);
        for (int j = 1; j <= N; j++) {
            if (depth[j] > max_depth) {
                max_depth = depth[j];
            }
        }

        long long sum = 0, count = 0;
        for (int d = 1; d <= max_depth; d++) {
            sum = (sum + d) % MOD;
            count++;
        }

        long long inv = pow_mod(count, MOD - 2);
        long long result = sum * inv % MOD;
        printf("%lld\n", result);
    }

    return 0;
}