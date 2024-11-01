#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MOD 998244353
#define MAXN 100005

typedef struct {
    int x, y;
} Point;

typedef struct {
    int u, v;
} Edge;

typedef struct {
    int size;
    int *vertices;
} Cycle;

Point points[MAXN];
Edge edges[MAXN];
Cycle cycles[MAXN];
int n, m, k, q;

int find_common_vertices(Cycle *c1, Cycle *c2) {
    int count = 0;
    for (int i = 0; i < c1->size; i++) {
        for (int j = 0; j < c2->size; j++) {
            if (c1->vertices[i] == c2->vertices[j]) {
                count++;
                break;
            }
        }
    }
    return count;
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d %d", &edges[i].u, &edges[i].v);
    }
    for (int i = 1; i <= k; i++) {
        scanf("%d", &cycles[i].size);
        cycles[i].vertices = (int *)malloc(cycles[i].size * sizeof(int));
        for (int j = 0; j < cycles[i].size; j++) {
            scanf("%d", &cycles[i].vertices[j]);
        }
    }
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        int z;
        scanf("%d", &z);
        int result = 0;
        // 暴力枚举所有大小为 z 的子集
        for (int mask = 0; mask < (1 << k); mask++) {
            if (__builtin_popcount(mask) == z) {
                int common_vertices = 0;
                for (int j = 0; j < k; j++) {
                    if (mask & (1 << j)) {
                        for (int l = j + 1; l < k; l++) {
                            if (mask & (1 << l)) {
                                common_vertices += find_common_vertices(&cycles[j + 1], &cycles[l + 1]);
                            }
                        }
                    }
                }
                result = (result + common_vertices) % MOD;
            }
        }
        printf("%d\n", result);
    }
    for (int i = 1; i <= k; i++) {
        free(cycles[i].vertices);
    }
    return 0;
}