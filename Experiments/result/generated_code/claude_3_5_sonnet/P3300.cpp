#include <stdio.h>
#include <string.h>

#define MAXN 100005
#define MAXM 7

char grid[MAXN][MAXM];
int N, M, Q;
int parent[MAXN * MAXM];
int size[MAXN * MAXM];
int rank[MAXN * MAXM];
int count[MAXN];

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (rank[x] < rank[y]) {
        parent[x] = y;
        size[y] += size[x];
    } else {
        parent[y] = x;
        size[x] += size[y];
        if (rank[x] == rank[y]) {
            rank[x]++;
        }
    }
}

int get_id(int r, int c) {
    return r * M + c;
}

void init() {
    for (int i = 0; i < N * M; i++) {
        parent[i] = i;
        size[i] = 1;
        rank[i] = 0;
    }
    memset(count, 0, sizeof(count));
}

void process_grid() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int id = get_id(i, j);
            if (grid[i][j] == 'O') {
                if (i > 0 && grid[i-1][j] == 'O') unite(id, get_id(i-1, j));
                if (j > 0 && grid[i][j-1] == 'O') unite(id, get_id(i, j-1));
            } else if (grid[i][j] == '+' || grid[i][j] == '|') {
                if (i > 0 && (grid[i-1][j] == 'O' || grid[i-1][j] == '+' || grid[i-1][j] == '|'))
                    unite(id, get_id(i-1, j));
            } else if (grid[i][j] == '+' || grid[i][j] == '-') {
                if (j > 0 && (grid[i][j-1] == 'O' || grid[i][j-1] == '+' || grid[i][j-1] == '-'))
                    unite(id, get_id(i, j-1));
            }
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (grid[i][j] == 'O') {
                int root = find(get_id(i, j));
                if (count[root] == 0) count[i+1]++;
                count[root]++;
            }
        }
    }
    for (int i = 1; i <= N; i++) {
        count[i] += count[i-1];
    }
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%s", grid[i]);
    }
    
    init();
    process_grid();
    
    scanf("%d", &Q);
    while (Q--) {
        char op;
        scanf(" %c", &op);
        if (op == 'C') {
            int i, j;
            char k;
            scanf("%d %d %c", &i, &j, &k);
            i--; j--;
            grid[i][j] = k;
            init();
            process_grid();
        } else {
            int l, r;
            scanf("%d %d", &l, &r);
            printf("%d\n", count[r] - count[l-1]);
        }
    }
    
    return 0;
}