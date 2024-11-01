#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 500005
#define MAXM 200005

int n, m;
int a[MAXN], b[MAXN];
int pos[MAXN], nxt[MAXN], pre[MAXN];
int stk[MAXN], top;
int happy[MAXM], tired[MAXM];
int x[MAXM];

void solve() {
    int i, j, k;
    int p = 1;
    top = 0;

    // 初始化
    for (i = 1; i <= n; i++) {
        pos[i] = -1;
        nxt[i] = -1;
        pre[i] = -1;
    }

    // 记录景点城市的下一个和上一个景点城市
    for (i = 1; i <= n; i++) {
        if (b[i]) {
            nxt[pos[a[i]]] = i;
            pre[i] = pos[a[i]];
            pos[a[i]] = i;
        }
    }

    // 遍历每个城市，确定每个月的休息城市
    for (i = 1; i <= m; i++) {
        int min_diff = n;
        int best_city = -1;

        // 处理栈顶城市
        while (top > 0 && stk[top] > p) {
            int city = stk[top];
            top--;

            // 计算快乐值和疲劳值差
            int diff = tired[i - 1] - happy[i - 1];
            if (diff < min_diff) {
                min_diff = diff;
                best_city = city;
            }
        }

        // 处理当前城市
        if (nxt[p] != -1) {
            stk[++top] = nxt[p];
        }
        if (pre[p] != -1) {
            stk[++top] = pre[p];
        }

        // 更新快乐值和疲劳值
        if (b[p]) {
            happy[i] = happy[i - 1] + 1;
        } else {
            happy[i] = happy[i - 1];
        }
        tired[i] = tired[i - 1] + 1;

        // 确定休息城市
        if (best_city != -1) {
            x[i] = a[best_city];
            p = best_city + 1;
        } else {
            x[i] = a[p];
            p++;
        }
    }

    // 输出结果
    for (i = 1; i <= m; i++) {
        printf("%d ", x[i]);
    }
    printf("\n");
}

int main() {
    int i;
    scanf("%d %d", &n, &m);
    for (i = 1; i <= n; i++) {
        scanf("%d %d", &a[i], &b[i]);
    }
    solve();
    return 0;
}