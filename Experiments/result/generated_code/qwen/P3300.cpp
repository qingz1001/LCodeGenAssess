#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXM 7

int N, M;
char grid[MAXN][MAXM];
int parent[MAXN * MAXM];
int rank[MAXN * MAXM];

void init() {
    for (int i = 0; i < N * M; i++) {
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

void unionSets(int x, int y) {
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

void update(int i, int j, char newChar) {
    int idx = (i - 1) * M + j - 1;
    if (grid[i][j] != newChar) {
        grid[i][j] = newChar;
        int currentIdx = idx;
        if (newChar == '+' || newChar == '|') {
            if (i > 1 && grid[i - 1][j] == 'O') unionSets(currentIdx, (i - 2) * M + j - 1);
            if (i < N && grid[i + 1][j] == 'O') unionSets(currentIdx, i * M + j - 1);
        }
        if (newChar == '+' || newChar == '-') {
            if (j > 1 && grid[i][j - 1] == 'O') unionSets(currentIdx, (i - 1) * M + j - 2);
            if (j < M && grid[i][j + 1] == 'O') unionSets(currentIdx, (i - 1) * M + j);
        }
    }
}

int countComponents() {
    int components = 0;
    for (int i = 0; i < N * M; i++) {
        if (parent[i] == i) components++;
    }
    return components;
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 1; i <= N; i++) {
        scanf("%s", grid[i] + 1);
    }
    init();
    int Q;
    scanf("%d", &Q);
    while (Q--) {
        char op;
        int a, b, c;
        scanf(" %c", &op);
        if (op == 'C') {
            scanf("%d %d %c", &a, &b, &c);
            update(a, b, c);
        } else if (op == 'Q') {
            scanf("%d %d", &a, &b);
            printf("%d\n", countComponents());
        }
    }
    return 0;
}