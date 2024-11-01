#include <stdio.h>
#include <math.h>

#define MAXN 25
#define MAXM 7

int n, m;
int a[MAXN];
double avg, sum, minSigma = 1e9;
int dp[MAXM][MAXN];

void dfs(int curGroup, int curSum) {
    if (curGroup == m) {
        double curAvg = curSum / (double)n;
        double curSigma = 0;
        for (int i = 0; i < n; i++) {
            curSigma += (curAvg - a[i]) * (curAvg - a[i]);
        }
        curSigma /= n;
        if (curSigma < minSigma) {
            minSigma = curSigma;
        }
        return;
    }
    for (int i = 0; i < n; i++) {
        if (dp[curGroup][i] == 0) {
            dp[curGroup][i] = 1;
            dfs(curGroup + 1, curSum + a[i]);
            dp[curGroup][i] = 0;
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    dfs(0, 0);
    printf("%.2f\n", sqrt(minSigma));
    return 0;
}