#include <stdio.h>
#include <stdlib.h>

#define MAXN 100000
#define MAXM 6

char grid[MAXN][MAXM];
int N, M, Q;

typedef struct {
    int parent;
    int rank;
} DisjointSet;

DisjointSet dsu[MAXN * MAXM];

int find(int x) {
    if (dsu[x].parent != x) {
        dsu[x].parent = find(dsu[x].parent);
    }
    return dsu[x].parent;
}

void unionSet(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX != rootY) {
        if (dsu[rootX].rank < dsu[rootY].rank) {
            dsu[rootX].parent = rootY;
        } else if (dsu[rootX].rank > dsu[rootY].rank) {
            dsu[rootY].parent = rootX;
        } else {
            dsu[rootY].parent = rootX;
            dsu[rootX].rank++;
        }
    }
}

void initializeDSU() {
    for (int i = 0; i < N * M; i++) {
        dsu[i].parent = i;
        dsu[i].rank = 0;
    }
}

void connectAdjacent(int x, int y) {
    int idx = x * M + y;
    if (x > 0 && (grid[x-1][y] == 'O' || grid[x-1][y] == '|' || grid[x-1][y] == '+')) {
        unionSet(idx, (x-1) * M + y);
    }
    if (x < N-1 && (grid[x+1][y] == 'O' || grid[x+1][y] == '|' || grid[x+1][y] == '+')) {
        unionSet(idx, (x+1) * M + y);
    }
    if (y > 0 && (grid[x][y-1] == 'O' || grid[x][y-1] == '-' || grid[x][y-1] == '+')) {
        unionSet(idx, x * M + y - 1);
    }
    if (y < M-1 && (grid[x][y+1] == 'O' || grid[x][y+1] == '-' || grid[x][y+1] == '+')) {
        unionSet(idx, x * M + y + 1);
    }
}

void changeCell(int i, int j, char k) {
    grid[i][j] = k;
    initializeDSU();
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < M; y++) {
            if (grid[x][y] == 'O') {
                connectAdjacent(x, y);
            }
        }
    }
}

int countConnectedComponents(int l, int r) {
    int count = 0;
    int seen[MAXN * MAXM] = {0};
    for (int x = l-1; x < r; x++) {
        for (int y = 0; y < M; y++) {
            if (grid[x][y] == 'O') {
                int root = find(x * M + y);
                if (!seen[root]) {
                    seen[root] = 1;
                    count++;
                }
            }
        }
    }
    return count;
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%s", grid[i]);
    }
    initializeDSU();
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < M; y++) {
            if (grid[x][y] == 'O') {
                connectAdjacent(x, y);
            }
        }
    }

    scanf("%d", &Q);
    for (int q = 0; q < Q; q++) {
        char op;
        scanf(" %c", &op);
        if (op == 'C') {
            int i, j;
            char k;
            scanf("%d %d %c", &i, &j, &k);
            changeCell(i-1, j-1, k);
        } else if (op == 'Q') {
            int l, r;
            scanf("%d %d", &l, &r);
            printf("%d\n", countConnectedComponents(l, r));
        }
    }

    return 0;
}