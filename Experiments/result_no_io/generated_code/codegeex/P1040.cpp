#include <stdio.h>
#include <stdlib.h>

#define MAXN 30
#define MAX_VAL 4000000000

int n;
int score[MAXN];
int maxScore[MAXN][MAXN];
int root[MAXN][MAXN];

void preOrder(int start, int end) {
    if (start > end) return;
    printf("%d ", root[start][end]);
    preOrder(start, root[start][end] - 1);
    preOrder(root[start][end] + 1, end);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &score[i]);
    }

    // Initialize maxScore and root arrays
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i > j) {
                maxScore[i][j] = 1;
                root[i][j] = i;
            } else {
                maxScore[i][j] = 0;
                root[i][j] = 0;
            }
        }
    }

    // Calculate maxScore and root for all subarrays
    for (int length = 1; length <= n; length++) {
        for (int i = 1; i <= n - length + 1; i++) {
            int j = i + length - 1;
            for (int k = i; k <= j; k++) {
                int leftScore = (k == i) ? 1 : maxScore[i][k - 1];
                int rightScore = (k == j) ? 1 : maxScore[k + 1][j];
                int currentScore = leftScore * rightScore + score[k];
                if (currentScore > maxScore[i][j]) {
                    maxScore[i][j] = currentScore;
                    root[i][j] = k;
                }
            }
        }
    }

    printf("%d\n", maxScore[1][n]);
    preOrder(1, n);
    printf("\n");

    return 0;
}