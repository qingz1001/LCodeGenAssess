#include <stdio.h>
#include <stdlib.h>

#define MAX_N 27
#define MAX_M 601

int visited[MAX_N];
int parent[MAX_N];

void initialize(int n) {
    for (int i = 0; i <= n; ++i) {
        visited[i] = 0;
        parent[i] = i;
    }
}

int find(int u) {
    if (parent[u] != u)
        parent[u] = find(parent[u]);
    return parent[u];
}

void union_sets(int u, int v) {
    int pu = find(u);
    int pv = find(v);
    if (pu != pv) {
        parent[pu] = pv;
    }
}

int is_cyclic(int n) {
    for (int i = 1; i <= n; ++i) {
        if (find(i) == i && visited[i]) {
            return 1;
        }
    }
    return 0;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    initialize(n);

    for (int i = 0; i < m; ++i) {
        char a, b;
        scanf(" %c <%c ", &a, &b);
        int ua = a - 'A' + 1;
        int ub = b - 'A' + 1;

        if (find(ua) == find(ub)) {
            printf("Inconsistency found after %d relations.\n", i + 1);
            return 0;
        }

        union_sets(ua, ub);
        visited[ua] = 1;
        if (is_cyclic(n)) {
            printf("Inconsistency found after %d relations.\n", i + 1);
            return 0;
        }
    }

    int sorted = 1;
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            sorted = 0;
            break;
        }
    }

    if (sorted) {
        printf("Sorted sequence determined after %d relations: ", m);
        for (int i = 1; i <= n; ++i) {
            printf("%c", find(i) - 1 + 'A');
        }
        printf(".\n");
    } else {
        printf("Sorted sequence cannot be determined.\n");
    }

    return 0;
}