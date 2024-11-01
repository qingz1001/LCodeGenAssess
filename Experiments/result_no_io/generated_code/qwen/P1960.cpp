#include <stdio.h>
#include <stdlib.h>

#define MAX_N 5000
#define MAX_M 100000

int parent[MAX_N + 1];
int rank[MAX_N + 1];

void init(int n) {
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void merge(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX == rootY) return;
    if (rank[rootX] > rank[rootY]) {
        parent[rootY] = rootX;
    } else if (rank[rootX] < rank[rootY]) {
        parent[rootX] = rootY;
    } else {
        parent[rootY] = rootX;
        rank[rootX]++;
    }
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    init(N);

    for (int i = 0; i < M; i++) {
        int X, Y;
        scanf("%d %d", &X, &Y);
        merge(X, Y);
    }

    int *result = (int *)malloc((N + 1) * sizeof(int));
    for (int i = 1; i <= N; i++) {
        result[find(i)]++;
    }

    for (int i = 1; i <= N; i++) {
        printf("%d ", i);
    }
    printf("\n");

    int has_other_rankings = 0;
    for (int i = 1; i <= N; i++) {
        if (result[i] > 1) {
            has_other_rankings = 1;
            break;
        }
    }

    printf("%d\n", has_other_rankings);

    free(result);
    return 0;
}