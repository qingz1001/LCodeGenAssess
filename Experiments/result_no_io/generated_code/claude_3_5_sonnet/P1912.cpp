#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 100005
#define MAX_L 3000005
#define INF 1e18

char sentences[MAX_N][35];
int len[MAX_N];
long long dp[MAX_N];
int prev[MAX_N];

long long badness(int i, int j, int L, int P) {
    long long spaces = j - i;
    long long chars = 0;
    for (int k = i; k <= j; k++) {
        chars += len[k];
    }
    long long total = chars + spaces;
    if (total > L) return INF;
    return (long long)pow(L - total, P);
}

void solve(int N, int L, int P) {
    for (int i = 1; i <= N; i++) {
        dp[i] = INF;
        for (int j = 0; j < i; j++) {
            long long cost = badness(j + 1, i, L, P);
            if (cost == INF) break;
            long long total_cost = (j == 0 ? 0 : dp[j]) + cost;
            if (total_cost < dp[i]) {
                dp[i] = total_cost;
                prev[i] = j;
            }
        }
    }

    if (dp[N] > INF) {
        printf("Too hard to arrange\n");
        return;
    }

    printf("%lld\n", dp[N]);

    int lines[MAX_N], line_count = 0;
    for (int i = N; i > 0; i = prev[i]) {
        lines[line_count++] = i;
    }

    for (int i = line_count - 1; i >= 0; i--) {
        int start = (i == line_count - 1 ? 1 : lines[i + 1] + 1);
        int end = lines[i];
        for (int j = start; j <= end; j++) {
            printf("%s", sentences[j]);
            if (j < end) printf(" ");
        }
        printf("\n");
    }
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int N, L, P;
        scanf("%d %d %d", &N, &L, &P);

        for (int i = 1; i <= N; i++) {
            scanf("%s", sentences[i]);
            len[i] = strlen(sentences[i]);
        }

        solve(N, L, P);
        printf("--------------------\n");
    }

    return 0;
}