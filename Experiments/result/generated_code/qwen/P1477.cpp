#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int n, m;
int seen[MAXN][MAXN];
int degree[MAXN];

void add_edge(int a, int b) {
    if (seen[a][b]) return;
    seen[a][b] = 1;
    degree[a]++;
    degree[b]--;
}

int find_max_classes() {
    int max_classes = 0;
    for (int i = 1; i <= n; i++) {
        if (degree[i] == 1) {
            max_classes++;
        }
    }
    return max_classes + 1;
}

int find_min_classes() {
    int min_classes = 0;
    for (int i = 1; i <= n; i++) {
        if (degree[i] == -1) {
            min_classes++;
        }
    }
    return min_classes + 1;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        add_edge(a, b);
    }

    int max_classes = find_max_classes();
    int min_classes = find_min_classes();

    if (min_classes < 3) {
        printf("-1 -1\n");
    } else {
        printf("%d %d\n", max_classes, min_classes);
    }

    return 0;
}