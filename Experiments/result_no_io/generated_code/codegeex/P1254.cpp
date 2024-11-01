#include <stdio.h>

int n;
int a[10];
int vis[100];
int cnt = 0;

void dfs(int pos, int sum) {
    if (pos == n) {
        for (int i = 0; i < n; i++) {
            vis[a[i]] = 1;
        }
        for (int i = 1; i < 100; i++) {
            if (!vis[i]) {
                return;
            }
        }
        cnt++;
        printf("%d\n", sum);
        for (int i = 0; i < n; i++) {
            printf("%d ", a[i]);
        }
        printf("\n");
        return;
    }
    for (int i = 1; i <= n * 8; i++) {
        if (vis[i]) continue;
        a[pos] = i;
        vis[i] = 1;
        dfs(pos + 1, sum + i);
        vis[i] = 0;
    }
}

int main() {
    scanf("%d", &n);
    dfs(0, 0);
    return 0;
}