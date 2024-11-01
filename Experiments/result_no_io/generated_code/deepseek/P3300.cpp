#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100000
#define MAXM 6

char grid[MAXN][MAXM];
int parent[MAXN * MAXM];
int rank[MAXN * MAXM];
int N, M;

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void union_sets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

int get_index(int i, int j) {
    return i * M + j;
}

void initialize_grid() {
    for (int i = 0; i < N * M; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

void update_grid(int i, int j, char k) {
    grid[i][j] = k;
    initialize_grid();

    for (int x = 0; x < N; x++) {
        for (int y = 0; y < M; y++) {
            if (grid[x][y] == 'O') {
                if (x > 0 && grid[x - 1][y] == 'O') {
                    union_sets(get_index(x, y), get_index(x - 1, y));
                }
                if (y > 0 && grid[x][y - 1] == 'O') {
                    union_sets(get_index(x, y), get_index(x, y - 1));
                }
            }
        }
    }
}

int count_connected_components(int l, int r) {
    int count = 0;
    int seen[MAXN * MAXM] = {0};

    for (int x = l; x <= r; x++) {
        for (int y = 0; y < M; y++) {
            if (grid[x][y] == 'O') {
                int root = find(get_index(x, y));
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

    initialize_grid();

    int Q;
    scanf("%d", &Q);
    while (Q--) {
        char op[2];
        scanf("%s", op);
        if (op[0] == 'C') {
            int i, j;
            char k;
            scanf("%d %d %c", &i, &j, &k);
            update_grid(i - 1, j - 1, k);
        } else if (op[0] == 'Q') {
            int l, r;
            scanf("%d %d", &l, &r);
            printf("%d\n", count_connected_components(l - 1, r - 1));
        }
    }

    return 0;
}