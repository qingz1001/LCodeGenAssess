#include <stdio.h>
#include <stdlib.h>

#define MAX_N 3000
#define MAX_M 2999

typedef struct Node {
    int id;
    int cost[MAX_M];
    int children[MAX_M];
    int num_children;
} Node;

Node tree[MAX_N];

int max_users = 0;

void dfs(int node, int budget) {
    if (budget >= 0) {
        max_users++;
    }
    for (int i = 0; i < tree[node].num_children; i++) {
        int child_id = tree[node].children[i];
        int child_cost = tree[node].cost[i];
        dfs(child_id, budget - child_cost);
    }
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    for (int i = 1; i <= N; i++) {
        tree[i].id = i;
        tree[i].num_children = 0;
    }

    for (int i = 1; i <= N - M; i++) {
        int K;
        scanf("%d", &K);
        for (int j = 0; j < K; j++) {
            int A, C;
            scanf("%d %d", &A, &C);
            tree[i].children[tree[i].num_children] = A;
            tree[i].cost[tree[i].num_children] = C;
            tree[A].num_children--;
        }
    }

    int user_fees[MAX_M];
    for (int i = 0; i < M; i++) {
        scanf("%d", &user_fees[i]);
    }

    for (int i = 1; i <= N - M; i++) {
        dfs(i, user_fees[i - 1]);
    }

    printf("%d\n", max_users);

    return 0;
}