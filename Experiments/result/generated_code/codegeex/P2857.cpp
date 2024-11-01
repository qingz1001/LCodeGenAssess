#include <stdio.h>
#include <string.h>

int n, b, ans;
int cow[1010][21], barn[21];
int vis[1010];

int main() {
    int i, j, k;
    scanf("%d%d", &n, &b);
    ans = 21;

    // 读取每头牛对牛棚的偏好顺序
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= b; j++) {
            scanf("%d", &cow[i][j]);
        }
    }

    // 读取每个牛棚的容量
    for (i = 1; i <= b; i++) {
        scanf("%d", &barn[i]);
    }

    // 枚举所有可能的牛棚排名组合
    for (i = 1; i <= b; i++) {
        for (j = 1; j <= b; j++) {
            if (i == j) continue;
            for (k = 1; k <= b; k++) {
                if (i == k || j == k) continue;
                memset(vis, 0, sizeof(vis));

                // 分配牛到牛棚
                for (int t = 1; t <= n; t++) {
                    for (int s = 1; s <= b; s++) {
                        if (cow[t][s] == i && vis[t] == 0 && barn[i] > 0) {
                            barn[i]--;
                            vis[t] = 1;
                            break;
                        } else if (cow[t][s] == j && vis[t] == 0 && barn[j] > 0) {
                            barn[j]--;
                            vis[t] = 1;
                            break;
                        } else if (cow[t][s] == k && vis[t] == 0 && barn[k] > 0) {
                            barn[k]--;
                            vis[t] = 1;
                            break;
                        }
                    }
                }

                // 检查是否有牛没有被分配到牛棚
                for (int t = 1; t <= n; t++) {
                    if (vis[t] == 0) {
                        goto next;
                    }
                }

                // 计算当前分配方案的最小排名跨度
                int min_rank = 21, max_rank = 0;
                for (int t = 1; t <= n; t++) {
                    for (int s = 1; s <= b; s++) {
                        if (vis[t] == 1) {
                            min_rank = (min_rank < cow[t][s]) ? min_rank : cow[t][s];
                            max_rank = (max_rank > cow[t][s]) ? max_rank : cow[t][s];
                        }
                    }
                }
                ans = (ans < max_rank - min_rank + 1) ? ans : max_rank - min_rank + 1;

                next:;
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}