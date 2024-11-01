#include <stdio.h>
#include <string.h>

int main() {
    int n;
    scanf("%d", &n);
    getchar(); // 读取换行符

    char a[30], b[30], c[30];
    gets(a);
    gets(b);
    gets(c);

    int val[30];
    int vis[30]; // 标记是否已经确定数值
    int num[30]; // 存储每个字母对应的数字
    memset(vis, 0, sizeof(vis));
    memset(num, -1, sizeof(num));

    // 初始化已知数字
    for (int i = 0; i < n; i++) {
        if (a[i] == b[i] && a[i] == c[i]) {
            num[a[i]] = c[i] - 'A';
            vis[a[i]] = 1;
        }
    }

    // 从高位到低位进行计算
    for (int i = n - 1; i >= 0; i--) {
        if (!vis[a[i]] && !vis[b[i]] && !vis[c[i]]) {
            for (int j = 0; j < n; j++) {
                if (num[j] == -1) {
                    num[j] = j;
                    vis[j] = 1;
                    break;
                }
            }
        }

        if (!vis[a[i]]) {
            num[a[i]] = (c[i] - num[c[i]] + num[b[i]] - 'A' + 1) % n;
            vis[a[i]] = 1;
        }

        if (!vis[b[i]]) {
            num[b[i]] = (c[i] - num[c[i]] + num[a[i]] - 'A' + 1) % n;
            vis[b[i]] = 1;
        }

        if (!vis[c[i]]) {
            num[c[i]] = (num[a[i]] - 'A' + num[b[i]] - 'A' + 1) % n;
            vis[c[i]] = 1;
        }
    }

    // 输出结果
    for (int i = 0; i < n; i++) {
        printf("%d ", num[i]);
    }
    printf("\n");

    return 0;
}