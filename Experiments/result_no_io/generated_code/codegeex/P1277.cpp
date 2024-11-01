#include <stdio.h>

int main() {
    int M[4][4];
    int rowSum[4], colSum[4], diagSum, antiDiagSum;
    int given[4][3];

    // 输入行、列和对角线之和
    scanf("%d %d %d %d", &rowSum[0], &rowSum[1], &rowSum[2], &rowSum[3]);
    scanf("%d %d %d %d", &colSum[0], &colSum[1], &colSum[2], &colSum[3]);
    scanf("%d %d", &diagSum, &antiDiagSum);

    // 输入已知的4个位置的元素值
    for (int i = 0; i < 4; i++) {
        scanf("%d %d %d", &given[i][0], &given[i][1], &given[i][2]);
        M[given[i][0]][given[i][1]] = given[i][2];
    }

    // 计算剩余的12个位置
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (M[i][j] == 0) {
                // 计算当前行列对角线之和的差值
                int rowDiff = rowSum[i] - (M[i][0] + M[i][1] + M[i][2] + M[i][3]);
                int colDiff = colSum[j] - (M[0][j] + M[1][j] + M[2][j] + M[3][j]);
                int diagDiff = (i == j) ? (diagSum - (M[0][0] + M[1][1] + M[2][2] + M[3][3])) : 0;
                int antiDiagDiff = (i + j == 3) ? (antiDiagSum - (M[0][3] + M[1][2] + M[2][1] + M[3][0])) : 0;

                // 计算当前位置的值
                M[i][j] = rowDiff + colDiff + diagDiff + antiDiagDiff - (M[0][0] + M[1][1] + M[2][2] + M[3][3]);
            }
        }
    }

    // 输出结果
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }

    return 0;
}