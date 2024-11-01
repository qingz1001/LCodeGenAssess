#include <stdio.h>
#include <string.h>

int main() {
    int n1, n2, i, j;
    char s1[101], s2[101];
    int dp[101][101];
    int score[5][5] = {
        {5, -1, -2, -1, -3},
        {-1, 5, -3, -2, -4},
        {-2, -3, 5, -2, -2},
        {-1, -2, -2, 5, -1},
        {-3, -4, -2, -1, 0}
    };

    // 读取输入
    scanf("%d %s", &n1, s1);
    scanf("%d %s", &n2, s2);

    // 初始化dp数组
    for (i = 0; i <= n1; i++) {
        dp[i][0] = 0;
    }
    for (i = 0; i <= n2; i++) {
        dp[0][i] = 0;
    }

    // 动态规划计算相似度
    for (i = 1; i <= n1; i++) {
        for (j = 1; j <= n2; j++) {
            int idx1, idx2;
            if (s1[i - 1] == 'A') idx1 = 0;
            else if (s1[i - 1] == 'C') idx1 = 1;
            else if (s1[i - 1] == 'G') idx1 = 2;
            else if (s1[i - 1] == 'T') idx1 = 3;
            else idx1 = 4;

            if (s2[j - 1] == 'A') idx2 = 0;
            else if (s2[j - 1] == 'C') idx2 = 1;
            else if (s2[j - 1] == 'G') idx2 = 2;
            else if (s2[j - 1] == 'T') idx2 = 3;
            else idx2 = 4;

            dp[i][j] = score[idx1][idx2] + fmax(dp[i - 1][j], fmax(dp[i][j - 1], dp[i - 1][j - 1]));
        }
    }

    // 输出结果
    printf("%d\n", dp[n1][n2]);

    return 0;
}