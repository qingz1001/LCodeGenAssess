#include <stdio.h>
#include <stdlib.h>

#define MAX_N 5005
#define MAX_K 1005
#define MAX_H 505

int n, k, h;
int tree[MAX_N][MAX_N];
int in_degree[MAX_N];
int position[MAX_K];
int food_positions[MAX_H];

void dfs(int node, int parent, int *visited, int *path, int *path_length) {
    visited[node] = 1;
    path[(*path_length)++] = node;

    for (int i = 1; i <= n; i++) {
        if (tree[node][i] && !visited[i]) {
            dfs(i, node, visited, path, path_length);
        }
    }

    visited[node] = 0;
}

int find_path(int start, int end) {
    int visited[MAX_N] = {0};
    int path[MAX_N], path_length = 0;
    dfs(start, -1, visited, path, &path_length);

    for (int i = 0; i < path_length; i++) {
        if (path[i] == end) {
            return i + 1;
        }
    }

    return -1;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            tree[i][j] = 0;
        }
    }

    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        tree[a][b] = 1;
        tree[b][a] = 1;
    }

    scanf("%d", &k);
    for (int i = 0; i < k; i++) {
        scanf("%d", &position[i]);
    }

    scanf("%d", &h);
    for (int i = 0; i < h; i++) {
        scanf("%d", &food_positions[i]);
    }

    for (int i = 0; i < k; i++) {
        int eaten_count = 0;
        int current_position = position[i];
        for (int j = 0; j < h; j++) {
            int path_length = find_path(current_position, food_positions[j]);
            if (path_length != -1) {
                eaten_count++;
                current_position = food_positions[j];
            }
        }
        printf("%d %d\n", current_position, eaten_count);
    }

    return 0;
}