#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 500
#define MAX_HEIGHT 1000000

int N;
int field[MAX_N][MAX_N];
int parent[MAX_N * MAX_N];
int size[MAX_N * MAX_N];

typedef struct {
    int x, y, diff;
} Edge;

Edge edges[4 * MAX_N * MAX_N];
int edge_count = 0;

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
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

int compare(const void* a, const void* b) {
    return ((Edge*)a)->diff - ((Edge*)b)->diff;
}

int main() {
    scanf("%d", &N);
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &field[i][j]);
        }
    }
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int idx = i * N + j;
            parent[idx] = idx;
            size[idx] = 1;
            
            if (i > 0) {
                edges[edge_count++] = (Edge){i * N + j, (i - 1) * N + j, abs(field[i][j] - field[i - 1][j])};
            }
            if (j > 0) {
                edges[edge_count++] = (Edge){i * N + j, i * N + j - 1, abs(field[i][j] - field[i][j - 1])};
            }
        }
    }
    
    qsort(edges, edge_count, sizeof(Edge), compare);
    
    int target = (N * N + 1) / 2;
    int result = 0;
    
    for (int i = 0; i < edge_count; i++) {
        int x = find(edges[i].x);
        int y = find(edges[i].y);
        
        if (x != y) {
            unite(x, y);
            if (size[find(x)] >= target) {
                result = edges[i].diff;
                break;
            }
        }
    }
    
    printf("%d\n", result);
    
    return 0;
}