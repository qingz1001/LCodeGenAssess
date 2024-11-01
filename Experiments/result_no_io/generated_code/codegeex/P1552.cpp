#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int boss;
    int cost;
    int leadership;
} Node;

int compare(const void *a, const void *b) {
    Node *nodeA = (Node *)a;
    Node *nodeB = (Node *)b;
    return nodeA->cost - nodeB->cost;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    Node *ninja = (Node *)malloc(N * sizeof(Node));
    for (int i = 0; i < N; i++) {
        scanf("%d %d %d", &ninja[i].boss, &ninja[i].cost, &ninja[i].leadership);
    }

    qsort(ninja, N, sizeof(Node), compare);

    int *dp = (int *)malloc((M + 1) * sizeof(int));
    for (int i = 0; i <= M; i++) {
        dp[i] = 0;
    }

    for (int i = 0; i < N; i++) {
        for (int j = M; j >= ninja[i].cost; j--) {
            dp[j] = (dp[j] > dp[j - ninja[i].cost] + ninja[i].leadership) ? dp[j] : dp[j - ninja[i].cost] + ninja[i].leadership;
        }
    }

    int result = 0;
    for (int i = 0; i <= M; i++) {
        result = (result > dp[i]) ? result : dp[i];
    }

    printf("%d\n", result);

    free(ninja);
    free(dp);

    return 0;
}