#include <stdio.h>
#include <string.h>

#define MAX_N 1000
#define MAX_M 1000

char grid[MAX_N][MAX_M + 1];
int parent[MAX_N * MAX_M];
int size[MAX_N * MAX_M];
int N, M, Q;

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x != y) {
        if (size[x] < size[y]) {
            int temp = x;
            x = y;
            y = temp;
        }
        parent[y] = x;
        size[x] += size[y];
    }
}

int get_index(int i, int j) {
    return i * M + j;
}

void init_dsu() {
    for (int i = 0; i < N * M; i++) {
        parent[i] = i;
        size[i] = 1;
    }
}

void process_grid() {
    int dx[] = {0, 1};
    int dy[] = {1, 0};
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < 2; k++) {
                int ni = i + dx[k];
                int nj = j + dy[k];
                if (ni < N && nj < M && grid[i][j] == grid[ni][nj]) {
                    unite(get_index(i, j), get_index(ni, nj));
                }
            }
        }
    }
}

int count_components(int x1, int y1, int x2, int y2) {
    int components = 0;
    int visited[MAX_N * MAX_M] = {0};
    
    for (int i = x1; i <= x2; i++) {
        for (int j = y1; j <= y2; j++) {
            int root = find(get_index(i, j));
            if (!visited[root]) {
                visited[root] = 1;
                components++;
            }
        }
    }
    
    return components;
}

int main() {
    scanf("%d %d %d", &N, &M, &Q);
    
    for (int i = 0; i < N; i++) {
        scanf("%s", grid[i]);
    }
    
    init_dsu();
    process_grid();
    
    for (int q = 0; q < Q; q++) {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        x1--; y1--; x2--; y2--;  // 转换为0-indexed
        
        int result = count_components(x1, y1, x2, y2);
        printf("%d\n", result);
    }
    
    return 0;
}