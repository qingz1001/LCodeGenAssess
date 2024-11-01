#include <stdio.h>
#include <stdlib.h>

#define MAX_N 300

typedef struct {
    int parent[MAX_N];
} Family;

int find(Family *family, int x) {
    if (family->parent[x] != x) {
        family->parent[x] = find(family, family->parent[x]);
    }
    return family->parent[x];
}

void union_sets(Family *family, int a, int b) {
    int root_a = find(family, a);
    int root_b = find(family, b);
    if (root_a != root_b) {
        family->parent[root_a] = root_b;
    }
}

double calculate_similarity(int a, int b, Family *family) {
    int root_a = find(family, a);
    int root_b = find(family, b);
    if (root_a == root_b) {
        return 100.0;
    } else {
        return 50.0;
    }
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    Family family;
    for (int i = 1; i <= n; i++) {
        family.parent[i] = i;
    }

    for (int i = 0; i < k; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        union_sets(&family, b, c);
        union_sets(&family, a, c);
    }

    int m;
    scanf("%d", &m);

    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        double similarity = calculate_similarity(a, b, &family);
        printf("%.1f\n", similarity);
    }

    return 0;
}