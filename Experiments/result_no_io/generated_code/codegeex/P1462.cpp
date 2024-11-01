#include <stdio.h>
#include <stdlib.h>

#define MAXN 10001
#define MAXM 50001

struct Edge {
    int u, v, w;
};

int n, m, b;
int fee[MAXN];
struct Edge edges[MAXM];
int fee_max[MAXN];

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    scanf("%d %d %d", &n, &m, &b);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &fee[i]);
        fee_max[i] = fee[i];
    }
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    qsort(fee + 1, n, sizeof(int), compare);

    int max_fee = 0;
    for (int i = 1; i <= n; i++) {
        if (b - fee[i] < 0) {
            printf("AFK\n");
            return 0;
        }
        max_fee = fee[i];
        int j;
        for (j = 0; j < m; j++) {
            if (edges[j].w > b - fee[i]) {
                break;
            }
            if (edges[j].u == i) {
                fee_max[edges[j].v] = fee_max[edges[j].u] > fee_max[edges[j].v] ? fee_max[edges[j].u] : fee_max[edges[j].v];
            } else if (edges[j].v == i) {
                fee_max[edges[j].u] = fee_max[edges[j].v] > fee_max[edges[j].u] ? fee_max[edges[j].v] : fee_max[edges[j].u];
            }
        }
        if (j == m) {
            break;
        }
    }

    qsort(fee_max + 1, n, sizeof(int), compare);
    printf("%d\n", fee_max[1]);

    return 0;
}