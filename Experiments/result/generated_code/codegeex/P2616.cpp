#include <stdio.h>

#define MAX_N 101
#define MAX_E 351

typedef struct {
    int x;
    int f;
    int c;
} Store;

Store stores[MAX_N];
int dp[MAX_E][MAX_N];

int main() {
    int K, E, N;
    scanf("%d %d %d", &K, &E, &N);

    for (int i = 0; i < N; i++) {
        scanf("%d %d %d", &stores[i].x, &stores[i].f, &stores[i].c);
    }

    // Sort stores by their positions
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (stores[i].x > stores[j].x) {
                Store temp = stores[i];
                stores[i] = stores[j];
                stores[j] = temp;
            }
        }
    }

    // Initialize dp array
    for (int i = 0; i <= E; i++) {
        for (int j = 0; j <= K; j++) {
            dp[i][j] = 0x7FFFFFFF; // Use a large number to represent infinity
        }
    }
    dp[0][0] = 0;

    // Dynamic programming to find the minimum cost
    for (int i = 0; i < N; i++) {
        for (int j = stores[i].x; j <= E; j++) {
            for (int k = K; k >= 0; k--) {
                int new_k = k + stores[i].f;
                if (new_k <= K) {
                    dp[j][new_k] = (dp[j][new_k] < dp[j - stores[i].x][k] + stores[i].f * stores[i].c) ? dp[j][new_k] : dp[j - stores[i].x][k] + stores[i].f * stores[i].c;
                }
            }
        }
    }

    // Find the minimum cost to reach location E with at least K pounds of feed
    int min_cost = 0x7FFFFFFF;
    for (int i = K; i <= K; i++) {
        min_cost = (min_cost < dp[E][i]) ? min_cost : dp[E][i];
    }

    printf("%d\n", min_cost);
    return 0;
}