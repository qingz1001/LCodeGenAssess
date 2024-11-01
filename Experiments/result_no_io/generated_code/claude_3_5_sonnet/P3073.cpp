#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 500
#define MAXH 1000001

int N, field[MAXN][MAXN];
int parent[MAXN*MAXN];
int size[MAXN*MAXN];
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

int find(int x) {
    if (parent[x] != x) parent[x] = find(parent[x]);
    return parent[x];
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x != y) {
        if (size[x] < size[y]) {
            int temp = x; x = y; y = temp;
        }
        parent[y] = x;
        size[x] += size[y];
    }
}

int valid(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < N;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &field[i][j]);
        }
    }

    int total = N * N;
    int half = (total + 1) / 2;
    
    for (int i = 0; i < total; i++) {
        parent[i] = i;
        size[i] = 1;
    }

    int edges[MAXN*MAXN*4][3];
    int edge_count = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < 4; k++) {
                int ni = i + dx[k], nj = j + dy[k];
                if (valid(ni, nj)) {
                    edges[edge_count][0] = abs(field[i][j] - field[ni][nj]);
                    edges[edge_count][1] = i * N + j;
                    edges[edge_count][2] = ni * N + nj;
                    edge_count++;
                }
            }
        }
    }

    for (int i = 0; i < edge_count; i++) {
        for (int j = i + 1; j < edge_count; j++) {
            if (edges[i][0] > edges[j][0]) {
                int temp[3];
                memcpy(temp, edges[i], sizeof(temp));
                memcpy(edges[i], edges[j], sizeof(temp));
                memcpy(edges[j], temp, sizeof(temp));
            }
        }
    }

    for (int i = 0; i < edge_count; i++) {
        int cost = edges[i][0];
        int u = edges[i][1], v = edges[i][2];
        unite(u, v);
        if (size[find(u)] >= half) {
            printf("%d\n", cost);
            return 0;
        }
    }

    return 0;
}