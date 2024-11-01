#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_SIZE 500
#define MAX_LANDMARKS 250000

int M, N;
int height[MAX_SIZE][MAX_SIZE];
int landmarks[MAX_SIZE][MAX_SIZE];
int parent[MAX_LANDMARKS];
int rank[MAX_LANDMARKS];

typedef struct {
    int x, y;
} Point;

Point landmark_points[MAX_LANDMARKS];
int landmark_count = 0;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int find_set(int x) {
    if (parent[x] != x)
        parent[x] = find_set(parent[x]);
    return parent[x];
}

void union_sets(int x, int y) {
    int root_x = find_set(x);
    int root_y = find_set(y);
    if (root_x == root_y) return;
    if (rank[root_x] < rank[root_y])
        parent[root_x] = root_y;
    else if (rank[root_x] > rank[root_y])
        parent[root_y] = root_x;
    else {
        parent[root_y] = root_x;
        rank[root_x]++;
    }
}

int is_valid(int x, int y) {
    return x >= 0 && x < M && y >= 0 && y < N;
}

int check_difficulty(int D) {
    for (int i = 0; i < landmark_count; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    for (int i = 0; i < landmark_count; i++) {
        for (int j = i + 1; j < landmark_count; j++) {
            int x1 = landmark_points[i].x, y1 = landmark_points[i].y;
            int x2 = landmark_points[j].x, y2 = landmark_points[j].y;
            if (abs(x1 - x2) + abs(y1 - y2) == 1 && abs(height[x1][y1] - height[x2][y2]) <= D) {
                union_sets(i, j);
            }
        }
    }

    int root = find_set(0);
    for (int i = 1; i < landmark_count; i++) {
        if (find_set(i) != root) return 0;
    }
    return 1;
}

int binary_search() {
    int left = 0, right = 1000000000;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (check_difficulty(mid))
            right = mid;
        else
            left = mid + 1;
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
            scanf("%d", &landmarks[i][j]);
            if (landmarks[i][j]) {
                landmark_points[landmark_count].x = i;
                landmark_points[landmark_count].y = j;
                landmark_count++;
            }
        }
    }

    int result = binary_search();
    printf("%d\n", result);

    return 0;
}