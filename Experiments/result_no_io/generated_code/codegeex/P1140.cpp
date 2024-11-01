#include <stdio.h>
#include <string.h>

#define MAXN 101

int score[5][5] = {
    {5, -1, -2, -1, -3},
    {-1, 5, -3, -2, -4},
    {-2, -3, 5, -2, -2},
    {-1, -2, -2, 5, -1},
    {-3, -4, -2, -1, 0}
};

int n;
char s1[MAXN], s2[MAXN];
int dp[MAXN][MAXN];

int getScore(char a, char b) {
    if (a == '-' || b == '-') {
        if (a == '-') return score[4][b - 'A'];
        return score[a - 'A'][4];
    }
    return score[a - 'A'][b - 'A'];
}

int max(int a, int b, int c) {
    return a > b ? (a > c ? a : c) : (b > c ? b : c);
}

int main() {
    scanf("%d%s", &n, s1);
    scanf("%d%s", &n, s2);

    memset(dp, 0, sizeof(dp));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dp[i][j] = max(dp[i-1][j-1] + getScore(s1[i-1], s2[j-1]),
                           dp[i-1][j] + getScore(s1[i-1], '-'),
                           dp[i][j-1] + getScore('-', s2[j-1]));
        }
    }

    printf("%d\n", dp[n][n]);
    return 0;
}