#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 500
#define MAX_M 500
#define INF 1000000000

int N, M;
int height[MAX_M][MAX_N];
int is_landmark[MAX_M][MAX_N];
int parent[MAX_M * MAX_N];
int rank[MAX_M * MAX_N];

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
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
        if (rank[x] == rank[y])
            rank[x]++;
    }
}

int is_valid(int x, int y) {
    return x >= 0 && x < M && y >= 0 && y < N;
}

int can_connect(int difficulty) {
    for (int i = 0; i < M * N; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < 4; k++) {
                int ni = i + dx[k];
                int nj = j + dy[k];
                if (is_valid(ni, nj) && abs(height[i][j] - height[ni][nj]) <= difficulty) {
                    unite(i * N + j, ni * N + nj);
                }
            }
        }
    }

    int first_landmark = -1;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (is_landmark[i][j]) {
                if (first_landmark == -1) {
                    first_landmark = find(i * N + j);
                } else if (find(i * N + j) != first_landmark) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

int binary_search() {
    int left = 0, right = INF;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (can_connect(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

int main() {
    scanf("%d %d", &M, &N);
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &height[i][j]);
        }
    }
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &is_landmark[i][j]);
        }
    }

    int result = binary_search();
    printf("%d\n", result);

    return 0;
}