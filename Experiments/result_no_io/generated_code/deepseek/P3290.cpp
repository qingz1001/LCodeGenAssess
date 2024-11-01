#include <stdio.h>
#include <string.h>

#define MOD 1000000007
#define MAXN 100
#define MAXM 12
#define MAXC 6
#define MAXQ 5

int n, m, c, q;
char templates[MAXQ][2][MAXC + 1];
int dp[MAXN + 1][1 << MAXM][1 << MAXM];

int count_matches(int row, int col, int mask1, int mask2) {
    if (row == n) return 1;
    if (col == m) return count_matches(row + 1, 0, mask2, 0);

    int state = dp[row][mask1][mask2];
    if (state != -1) return state;

    int result = 0;
    for (int i = 0; i < 3; i++) {
        int new_mask1 = mask1;
        int new_mask2 = mask2;

        for (int t = 0; t < q; t++) {
            int match = 1;
            for (int j = 0; j < c; j++) {
                int bit1 = (mask1 >> (col + j)) & 1;
                int bit2 = (mask2 >> (col + j)) & 1;
                char ch = (i == 0) ? 'W' : (i == 1) ? 'B' : 'X';
                if (templates[t][0][j] != ch && templates[t][0][j] != 'X') match = 0;
                if (templates[t][1][j] != ch && templates[t][1][j] != 'X') match = 0;
            }
            if (match) {
                new_mask1 |= (1 << (col + c - 1));
                new_mask2 |= (1 << (col + c - 1));
            }
        }

        result = (result + count_matches(row, col + 1, new_mask1, new_mask2)) % MOD;
    }

    dp[row][mask1][mask2] = result;
    return result;
}

int main() {
    scanf("%d %d %d %d", &n, &m, &c, &q);
    for (int i = 0; i < q; i++) {
        scanf("%s", templates[i][0]);
        scanf("%s", templates[i][1]);
    }

    memset(dp, -1, sizeof(dp));
    int result = count_matches(0, 0, 0, 0);
    printf("%d\n", result);

    return 0;
}