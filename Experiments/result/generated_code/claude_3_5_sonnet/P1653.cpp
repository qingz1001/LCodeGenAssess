#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 500

int W, L;
int map[MAX_SIZE][MAX_SIZE];
int parent[MAX_SIZE * MAX_SIZE];
int rank[MAX_SIZE * MAX_SIZE];

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
    } else {
        parent[y] = x;
        if (rank[x] == rank[y]) {
            rank[x]++;
        }
    }
}

int main() {
    scanf("%d %d", &W, &L);
    
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < W; j++) {
            scanf("%d", &map[i][j]);
        }
    }
    
    for (int i = 0; i < W * L; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
    
    int dx[] = {0, 1, 0, -1};
    int dy[] = {1, 0, -1, 0};
    
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < W; j++) {
            for (int k = 0; k < 4; k++) {
                int ni = i + dx[k];
                int nj = j + dy[k];
                if (ni >= 0 && ni < L && nj >= 0 && nj < W && map[i][j] >= map[ni][nj]) {
                    unite(i * W + j, ni * W + nj);
                }
            }
        }
    }
    
    int components = 0;
    for (int i = 0; i < W * L; i++) {
        if (find(i) == i) {
            components++;
        }
    }
    
    printf("%d\n", components - 1);
    
    return 0;
}