#include <stdio.h>

int main() {
    int n, m, k, x, y;
    scanf("%d%d%d%d%d", &n, &m, &k, &x, &y);

    // Initialize the number of paths array
    long long paths[105][105] = {0};
    paths[n][1] = 1; // Starting point

    // Calculate the number of paths
    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= m; j++) {
            if (i < n) {
                paths[i-1][j] = (paths[i-1][j] + paths[i][j]) % k;
            }
            if (j < m) {
                paths[i][j+1] = (paths[i][j+1] + paths[i][j]) % k;
            }
        }
    }

    // Output the result
    printf("%lld\n", paths[x-1][y]);
    return 0;
}