#include <stdio.h>
#include <string.h>

#define MAX_N 1005

int n;
int grid[MAX_N][MAX_N];
int dp[MAX_N][MAX_N][3];

int main() {
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");

    fscanf(in, "%d", &n);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= 2*i-1; j++) {
            fscanf(in, "%d", &grid[i][j]);
        }
    }

    int result = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= 2*i-1; j++) {
            if (grid[i][j]) {
                dp[i][j][0] = dp[i-1][j-1][0] + 1;
                dp[i][j][1] = dp[i-1][j][1] + 1;
                dp[i][j][2] = dp[i-1][j+1][2] + 1;

                if (j % 2 == 1) {
                    if (dp[i][j][0] >= 2 && dp[i][j][1] >= 2)
                        result += (dp[i][j][0] < dp[i][j][1]) ? dp[i][j][0] - 1 : dp[i][j][1] - 1;
                } else {
                    if (dp[i][j][1] >= 2 && dp[i][j][2] >= 2)
                        result += (dp[i][j][1] < dp[i][j][2]) ? dp[i][j][1] - 1 : dp[i][j][2] - 1;
                }
            }
        }
    }

    fprintf(out, "%d\n", result);

    fclose(in);
    fclose(out);
    return 0;
}