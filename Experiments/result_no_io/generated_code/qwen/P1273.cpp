#include <stdio.h>
#include <stdlib.h>

#define MAX_N 3000
#define MAX_M 2999

typedef struct {
    int id;
    int cost;
} Node;

Node tree[MAX_N + 1];
int users[MAX_M + 1];
int n, m;

int dfs(int node, int budget) {
    if (node > n - m) {
        return 1;
    }
    int max_users = 0;
    for (int i = 2 * node; i <= 2 * node + tree[node].id; i += 2) {
        if (budget >= tree[node].cost) {
            max_users += dfs(i / 2, budget - tree[node].cost);
        }
    }
    if (budget >= users[node - n + m]) {
        max_users++;
    }
    return max_users;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 2; i <= n; i++) {
        scanf("%d", &tree[i].id);
        for (int j = 1; j <= tree[i].id; j++) {
            scanf("%d %d", &tree[2 * i + j - 1].id, &tree[2 * i + j - 1].cost);
        }
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d", &users[i]);
    }

    int max_users = 0;
    for (int budget = 0; budget <= 10; budget++) {
        max_users = fmax(max_users, dfs(1, budget));
    }

    printf("%d\n", max_users);

    return 0;
}