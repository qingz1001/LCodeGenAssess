#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000001

typedef struct {
    int parent;
    int a;
    int b;
    int size;
    double ratio;
} Node;

Node nodes[MAXN];
int n;

double calculateRatio(int root) {
    if (nodes[root].size == 1) return (double)nodes[root].a / nodes[root].b;
    double sum_a = nodes[root].a, sum_b = nodes[root].b;
    for (int i = 2; i <= n; ++i) {
        if (nodes[i].parent == root) {
            sum_a += nodes[i].a * nodes[i].size;
            sum_b += nodes[i].b * nodes[i].size;
        }
    }
    return (double)sum_a / sum_b;
}

void dfs(int root) {
    nodes[root].size = 1;
    for (int i = 2; i <= n; ++i) {
        if (nodes[i].parent == root) {
            dfs(i);
            nodes[root].size += nodes[i].size;
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 2; i <= n; ++i) {
        scanf("%d", &nodes[i].parent);
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%d %d", &nodes[i].a, &nodes[i].b);
    }

    dfs(1);

    long long W = 0;
    int count = 0;
    while (1) {
        int max_ratio_index = 1;
        double max_ratio = calculateRatio(max_ratio_index);
        for (int i = 2; i <= n; ++i) {
            if (nodes[i].parent != -1 && calculateRatio(i) > max_ratio) {
                max_ratio_index = i;
                max_ratio = calculateRatio(i);
            }
        }
        if (max_ratio_index == 1) break;
        W += (count + 1) * ((long long)(max_ratio + 0.5));
        count++;
        nodes[max_ratio_index].parent = -1;
        for (int i = 2; i <= n; ++i) {
            if (nodes[i].parent == max_ratio_index) {
                nodes[nodes[i].parent].a += nodes[i].a * nodes[i].size;
                nodes[nodes[i].parent].b += nodes[i].b * nodes[i].size;
                nodes[i].parent = -1;
            }
        }
    }

    printf("%lld\n", W);

    return 0;
}