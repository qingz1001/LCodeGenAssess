#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100001
#define MAXW 1000000001

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int w[MAXN], m_j;
    for (int i = 0; i < n; i++) {
        scanf("%d", &w[i]);
    }

    int weights[MAXW] = {0};
    for (int i = 0; i < m; i++) {
        scanf("%d", &m_j);
        weights[m_j]++;
    }

    // 对砝码进行降序排序
    for (int i = MAXW - 1; i > 0; i--) {
        weights[i] += weights[i - 1];
        weights[i - 1] = 0;
    }

    int maxWeights = 0;
    for (int i = 0; i < n; i++) {
        maxWeights += weights[w[i]];
    }

    printf("%d\n", maxWeights);

    return 0;
}