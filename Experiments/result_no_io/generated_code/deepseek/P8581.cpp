#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 1000005

typedef struct Node {
    int parent;
    int a;
    int b;
    int children_count;
    int *children;
} Node;

Node nodes[MAXN];
int n;

void read_input() {
    scanf("%d", &n);
    for (int i = 2; i <= n; i++) {
        scanf("%d", &nodes[i].parent);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &nodes[i].a);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &nodes[i].b);
    }
}

void build_tree() {
    for (int i = 1; i <= n; i++) {
        nodes[i].children_count = 0;
        nodes[i].children = NULL;
    }
    for (int i = 2; i <= n; i++) {
        int parent = nodes[i].parent;
        nodes[parent].children_count++;
        nodes[parent].children = realloc(nodes[parent].children, nodes[parent].children_count * sizeof(int));
        nodes[parent].children[nodes[parent].children_count - 1] = i;
    }
}

int dfs(int node, int *a_sum, int *b_sum) {
    *a_sum = nodes[node].a;
    *b_sum = nodes[node].b;
    int min_ratio = (*a_sum) / (*b_sum);
    int max_nodes = 1;

    for (int i = 0; i < nodes[node].children_count; i++) {
        int child = nodes[node].children[i];
        int child_a_sum, child_b_sum;
        int child_nodes = dfs(child, &child_a_sum, &child_b_sum);
        *a_sum += child_a_sum;
        *b_sum += child_b_sum;
        int ratio = (*a_sum) / (*b_sum);
        if (ratio < min_ratio || (ratio == min_ratio && child_nodes + 1 > max_nodes)) {
            min_ratio = ratio;
            max_nodes = child_nodes + 1;
        }
    }

    return max_nodes;
}

long long calculate_W() {
    int a_sum, b_sum;
    int m = dfs(1, &a_sum, &b_sum);
    long long W = 0;
    for (int i = 1; i <= m; i++) {
        W += i * ceil((double)a_sum / b_sum);
    }
    return W;
}

int main() {
    read_input();
    build_tree();
    long long result = calculate_W();
    printf("%lld\n", result);
    return 0;
}