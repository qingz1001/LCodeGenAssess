#include <stdio.h>
#include <string.h>

int N, M, P;
int sum[210][210];
int ans[210][210];

int main() {
    scanf("%d%d%d", &N, &M, &P);
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= M; j++)
            scanf("%d", &sum[i][j]);

    // Initialize the answer matrix with 0
    memset(ans, 0, sizeof(ans));

    // Fill the first row and first column
    for (int i = 1; i <= N; i++) ans[i][1] = sum[i][1];
    for (int j = 1; j <= M; j++) ans[1][j] = sum[1][j];

    // Fill the rest of the matrix
    for (int i = 2; i <= N; i++) {
        for (int j = 2; j <= M; j++) {
            // Calculate the current cell value
            ans[i][j] = sum[i][j] - ans[i-1][j] - ans[i][j-1] + ans[i-1][j-1];
        }
    }

    // Output the matrix
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            printf("%d ", ans[i][j]);
        }
        printf("\n");
    }

    return 0;
}