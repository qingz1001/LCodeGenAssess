#include <stdio.h>
#include <stdlib.h>

#define MAXN 30
#define INF 0x3f3f3f3f

typedef struct TreeNode {
    int val;
    struct TreeNode *left, *right;
} TreeNode;

int dp[MAXN][MAXN];
int preOrder[MAXN];

void dfs(int inLeft, int inRight, int *preIndex) {
    if (inLeft > inRight) return;
    int rootVal = dp[inLeft][inRight];
    for (int i = inLeft; i <= inRight; ++i) {
        if (dp[inLeft][i - 1] + dp[i + 1][inRight] + rootVal == dp[inLeft][inRight]) {
            TreeNode *root = (TreeNode *)malloc(sizeof(TreeNode));
            root->val = rootVal;
            root->left = NULL;
            root->right = NULL;
            preOrder[*preIndex++] = rootVal;
            dfs(inLeft, i - 1, preIndex);
            dfs(i + 1, inRight, preIndex);
            break;
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    int scores[MAXN];
    for (int i = 0; i < n; ++i) {
        scanf("%d", &scores[i]);
    }

    for (int i = 0; i < n; ++i) {
        dp[i][i] = scores[i];
    }

    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            dp[i][j] = INF;
            for (int k = i; k <= j; ++k) {
                int leftSum = (k == i) ? 1 : dp[i][k - 1];
                int rightSum = (k == j) ? 1 : dp[k + 1][j];
                dp[i][j] = fmin(dp[i][j], leftSum * rightSum + scores[k]);
            }
        }
    }

    printf("%d\n", dp[0][n - 1]);

    int preIndex = 0;
    dfs(0, n - 1, &preIndex);

    for (int i = 0; i < n; ++i) {
        if (i != 0) printf(" ");
        printf("%d", preOrder[i]);
    }
    printf("\n");

    return 0;
}