#include <stdio.h>
#include <string.h>

int main() {
    int n;
    scanf("%d", &n);
    
    char a[30], b[30], c[30];
    scanf("%s %s %s", a, b, c);
    
    int x[30], y[30], z[30], vis[30], ans[30];
    memset(vis, 0, sizeof(vis));
    
    // 初始化
    for (int i = 0; i < n; i++) {
        x[i] = a[i] - 'A';
        y[i] = b[i] - 'A';
        z[i] = c[i] - 'A';
        vis[x[i]] = 1;
        vis[y[i]] = 1;
        vis[z[i]] = 1;
    }
    
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (vis[i] == 0) {
            ans[i] = cnt++;
        }
    }
    
    int flag = 1;
    while (flag) {
        flag = 0;
        for (int i = 0; i < n; i++) {
            if (ans[x[i]] == -1) {
                ans[x[i]] = ans[z[i]] - ans[y[i]];
                if (ans[x[i]] < 0) {
                    ans[x[i]] += n;
                }
                if (vis[ans[x[i]]] == 1) {
                    ans[x[i]] = -1;
                    flag = 1;
                } else {
                    vis[ans[x[i]]] = 1;
                }
            }
            if (ans[y[i]] == -1) {
                ans[y[i]] = ans[z[i]] - ans[x[i]];
                if (ans[y[i]] < 0) {
                    ans[y[i]] += n;
                }
                if (vis[ans[y[i]]] == 1) {
                    ans[y[i]] = -1;
                    flag = 1;
                } else {
                    vis[ans[y[i]]] = 1;
                }
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        printf("%d ", ans[x[i]]);
    }
    printf("\n");
    
    return 0;
}