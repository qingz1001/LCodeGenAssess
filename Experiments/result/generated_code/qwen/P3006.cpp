#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXK 10005

typedef struct {
    int p;
    int c;
    int m;
} Field;

int n, k;
Field fields[MAXN];
int queries[MAXK];

long long dfs(int node, int parent, int time) {
    if (node == 1) {
        return fields[node].c;
    }

    long long total_cows = 0;
    for (int i = 2; i <= n; i++) {
        if (fields[i].p == node && i != parent) {
            total_cows += dfs(i, node, time);
        }
    }

    if (time >= fields[node].m) {
        total_cows += fields[node].c;
    }

    return total_cows;
}

int main() {
    scanf("%d %d", &n, &k);

    for (int i = 2; i <= n; i++) {
        scanf("%d %d %d", &fields[i].p, &fields[i].c, &fields[i].m);
    }

    for (int i = 0; i < k; i++) {
        scanf("%d", &queries[i]);
    }

    for (int i = 0; i < k; i++) {
        printf("%lld\n", dfs(1, 0, queries[i]));
    }

    return 0;
}