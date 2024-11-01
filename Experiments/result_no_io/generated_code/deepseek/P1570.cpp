#include <stdio.h>
#include <stdlib.h>

#define MAXN 200

int n, m;
int v[MAXN], c[MAXN];

double max_efficiency = 0.0;

void dfs(int idx, int cnt, int sum_v, int sum_c) {
    if (cnt == m) {
        double efficiency = (double)sum_v / sum_c;
        if (efficiency > max_efficiency) {
            max_efficiency = efficiency;
        }
        return;
    }
    if (idx >= n) return;

    // 选择当前调料
    dfs(idx + 1, cnt + 1, sum_v + v[idx], sum_c + c[idx]);

    // 不选择当前调料
    dfs(idx + 1, cnt, sum_v, sum_c);
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &c[i]);
    }

    dfs(0, 0, 0, 0);

    printf("%.3f\n", max_efficiency);

    return 0;
}