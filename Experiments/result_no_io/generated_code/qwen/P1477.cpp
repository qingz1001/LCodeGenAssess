#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int n, m;
int a[MAXN], b[MAXN];
int in_degree[MAXN];

void add_edge(int u, int v) {
    a[m] = u;
    b[m] = v;
    m++;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a[i], &b[i]);
        in_degree[b[i]]++;
    }

    int max_classes = 0;
    int min_classes = 0;

    // Find the maximum number of classes
    for (int i = 1; i <= n; i++) {
        if (in_degree[i] == 0) {
            max_classes++;
        }
    }

    // Find the minimum number of classes
    for (int i = 1; i <= n; i++) {
        if (in_degree[i] > 0) {
            min_classes++;
        }
    }

    if (max_classes < 3 || min_classes < 3) {
        printf("-1 -1\n");
    } else {
        printf("%d %d\n", max_classes, min_classes);
    }

    return 0;
}