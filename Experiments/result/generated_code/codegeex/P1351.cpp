#include <stdio.h>

#define MOD 10007

int n;
int w[200005];
int degree[200005];
int maxW = 0;
int sum = 0;

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        degree[u]++;
        degree[v]++;
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &w[i]);
        sum = (sum + w[i]) % MOD;
        if (degree[i] == 1) {
            maxW = maxW > w[i] ? maxW : w[i];
        }
    }
    int maxWeight = 0;
    int totalWeight = 0;
    for (int i = 1; i <= n; i++) {
        if (degree[i] == 1) {
            totalWeight = (totalWeight + maxW * w[i]) % MOD;
        }
    }
    printf("%d %d\n", maxWeight, totalWeight);
    return 0;
}