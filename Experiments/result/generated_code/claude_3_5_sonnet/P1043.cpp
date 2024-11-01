#include <stdio.h>
#include <string.h>

#define MAX_N 50
#define MAX_M 9
#define INF 0x3f3f3f3f

int n, m;
int nums[MAX_N * 2];
int dp_min[MAX_N * 2][MAX_M + 1];
int dp_max[MAX_N * 2][MAX_M + 1];

int mod(int x) {
    return (x % 10 + 10) % 10;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
        nums[i + n] = nums[i];
    }

    memset(dp_min, 0x3f, sizeof(dp_min));
    memset(dp_max, 0, sizeof(dp_max));

    for (int i = 0; i < 2 * n; i++) {
        dp_min[i][1] = dp_max[i][1] = mod(nums[i]);
    }

    for (int j = 2; j <= m; j++) {
        for (int i = 0; i < 2 * n; i++) {
            int sum = 0;
            for (int k = i; k < 2 * n; k++) {
                sum = mod(sum + nums[k]);
                if (k - i + 1 >= n) break;
                for (int p = 1; p < j; p++) {
                    int min_val = dp_min[k + 1][j - p] * sum;
                    int max_val = dp_max[k + 1][j - p] * sum;
                    if (min_val < dp_min[i][j]) dp_min[i][j] = min_val;
                    if (max_val > dp_max[i][j]) dp_max[i][j] = max_val;
                }
            }
        }
    }

    int min_result = INF, max_result = 0;
    for (int i = 0; i < n; i++) {
        if (dp_min[i][m] < min_result) min_result = dp_min[i][m];
        if (dp_max[i][m] > max_result) max_result = dp_max[i][m];
    }

    printf("%d\n%d\n", min_result, max_result);

    return 0;
}