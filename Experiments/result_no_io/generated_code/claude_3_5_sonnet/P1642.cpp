#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100
#define MAX_COMBINATIONS 1000000

int N, M;
int w[MAX_N], c[MAX_N];
int graph[MAX_N][MAX_N];
int visited[MAX_N];
int combination[MAX_N];
int best_combination[MAX_N];
double max_ratio = 0.0;

void dfs(int node) {
    visited[node] = 1;
    for (int i = 0; i < N; i++) {
        if (graph[node][i] && !visited[i]) {
            dfs(i);
        }
    }
}

int is_connected() {
    memset(visited, 0, sizeof(visited));
    int start;
    for (start = 0; start < N; start++) {
        if (combination[start] == 1) break;
    }
    dfs(start);
    for (int i = 0; i < N; i++) {
        if (combination[i] == 1 && !visited[i]) {
            return 0;
        }
    }
    return 1;
}

void generate_combinations(int index, int count) {
    if (count == N - M) {
        if (is_connected()) {
            int total_w = 0, total_c = 0;
            for (int i = 0; i < N; i++) {
                if (combination[i] == 1) {
                    total_w += w[i];
                    total_c += c[i];
                }
            }
            double ratio = (double)total_w / total_c;
            if (ratio > max_ratio) {
                max_ratio = ratio;
                memcpy(best_combination, combination, sizeof(combination));
            }
        }
        return;
    }
    if (index >= N) return;
    
    combination[index] = 1;
    generate_combinations(index + 1, count + 1);
    combination[index] = 0;
    generate_combinations(index + 1, count);
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d", &w[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &c[i]);
    }
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;
        graph[a][b] = graph[b][a] = 1;
    }

    generate_combinations(0, 0);

    printf("%.1f\n", max_ratio);

    return 0;
}