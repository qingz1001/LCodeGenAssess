#include <stdio.h>
#include <stdlib.h>

#define MAX_N 12

int n;
int x[MAX_N], y[MAX_N];
int pairs[MAX_N / 2][2];

int dfs(int pos, int used[]) {
    if (pos == n / 2) return 1;
    for (int i = 0; i < n / 2; i++) {
        if (!used[i]) {
            used[i] = 1;
            int a = pairs[i][0], b = pairs[i][1];
            if ((y[a] > y[b] && x[a] <= x[b]) || (y[a] < y[b] && x[a] >= x[b])) {
                used[i] = 0;
                continue;
            }
            int next_a = (a + 1) % n / 2, next_b = (b + 1) % n / 2;
            if (next_a != pos) {
                used[i] = 0;
                continue;
            }
            int ret = dfs(pos + 1, used);
            if (ret) return ret;
            used[i] = 0;
        }
    }
    return 0;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &x[i], &y[i]);
    }
    for (int i = 0; i < n / 2; i++) {
        pairs[i][0] = i * 2;
        pairs[i][1] = i * 2 + 1;
    }
    int ans = 0;
    int used[MAX_N / 2] = {0};
    for (int i = 0; i < n / 2; i++) {
        for (int j = i + 1; j < n / 2; j++) {
            pairs[0][0] = i * 2;
            pairs[0][1] = i * 2 + 1;
            pairs[1][0] = j * 2;
            pairs[1][1] = j * 2 + 1;
            if (dfs(2, used)) {
                ans++;
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}