#include <stdio.h>
#include <string.h>

#define MAX_H 6
#define MAX_ANS 1000000007

int h;
char view1[MAX_H + 1][MAX_H * 2 + 1];
char view2[MAX_H + 1][MAX_H * 2 + 1];
int dp[MAX_H + 1][MAX_H + 1][MAX_H * 2 + 1][MAX_H * 2 + 1];

int main() {
    // 读取高度
    scanf("%d", &h);
    // 读取两个视角的视图
    for (int i = 1; i <= h; i++) {
        scanf("%s", view1[i] + 1);
    }
    for (int i = 1; i <= h; i++) {
        scanf("%s", view2[i] + 1);
    }

    // 初始化动态规划数组
    memset(dp, 0, sizeof(dp));
    dp[0][0][1][1] = 1;

    // 动态规划
    for (int i = 0; i < h; i++) {
        for (int j = 0; j <= i; j++) {
            for (int k = 1; k <= h * 2; k++) {
                for (int l = 1; l <= h * 2; l++) {
                    if (dp[i][j][k][l] > 0) {
                        // 放置一个竖直的方块
                        if (k + 1 <= h * 2 && l - 1 >= 1 && view1[i + 1][k] == ' ' && view1[i + 1][l - 1] == ' ' && view2[i + 1][k] == ' ' && view2[i + 1][l - 1] == ' ') {
                            dp[i + 1][j][k + 1][l - 1] = (dp[i + 1][j][k + 1][l - 1] + dp[i][j][k][l]) % MAX_ANS;
                        }
                        // 放置一个水平的方块
                        if (k + 2 <= h * 2 && l - 2 >= 1 && view1[i + 1][k] == ' ' && view1[i + 1][k + 1] == ' ' && view1[i + 1][l - 1] == ' ' && view1[i + 1][l - 2] == ' ' && view2[i + 1][k] == ' ' && view2[i + 1][k + 1] == ' ' && view2[i + 1][l - 1] == ' ' && view2[i + 1][l - 2] == ' ') {
                            dp[i + 1][j + 1][k + 2][l - 2] = (dp[i + 1][j + 1][k + 2][l - 2] + dp[i][j][k][l]) % MAX_ANS;
                        }
                    }
                }
            }
        }
    }

    // 计算最终答案
    int ans = 0;
    for (int k = 1; k <= h * 2; k++) {
        for (int l = 1; l <= h * 2; l++) {
            ans = (ans + dp[h][h][k][l]) % MAX_ANS;
        }
    }

    // 输出答案
    printf("%d\n", ans);
    return 0;
}