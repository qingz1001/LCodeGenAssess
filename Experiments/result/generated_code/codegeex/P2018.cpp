#include <stdio.h>
#include <stdlib.h>

#define MAXN 1001

int n;
int parent[MAXN];
int subtree_size[MAXN];
int max_depth[MAXN];
int best_time = 0;
int best_choices[MAXN];
int num_best_choices = 0;

void dfs(int node) {
    if (node == 0) return;
    dfs(parent[node]);
    subtree_size[node] = 1;
    max_depth[node] = max_depth[parent[node]] + 1;
    for (int i = 0; i < n; i++) {
        if (parent[i] == node) {
            dfs(i);
            subtree_size[node] += subtree_size[i];
            max_depth[node] = (max_depth[node] > max_depth[i] + 1) ? max_depth[node] : max_depth[i] + 1;
        }
    }
}

void find_best_choices(int node) {
    if (node == 0) return;
    int time = max_depth[node] + subtree_size[node] - 1;
    if (time < best_time) {
        best_time = time;
        num_best_choices = 0;
    }
    if (time == best_time) {
        best_choices[num_best_choices++] = node;
    }
    for (int i = 0; i < n; i++) {
        if (parent[i] == node) {
            find_best_choices(i);
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        scanf("%d", &parent[i]);
    }

    dfs(0);
    find_best_choices(0);

    printf("%d\n", best_time);
    for (int i = 0; i < num_best_choices; i++) {
        printf("%d ", best_choices[i]);
    }
    printf("\n");

    return 0;
}