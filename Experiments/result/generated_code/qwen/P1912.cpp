#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100005
#define MAX_L 30
#define INF 1e18

typedef long long ll;

int N, L, P;
char sentences[MAX_N][MAX_L + 1];
ll dp[MAX_N];

ll cost(int start, int end) {
    int len = 0;
    for (int i = start; i <= end; i++) {
        len += strlen(sentences[i]);
        if (i != end) len++;
    }
    return abs(len - L);
}

void solve() {
    dp[0] = 0;
    for (int i = 1; i <= N; i++) {
        dp[i] = INF;
        for (int j = 0; j < i; j++) {
            dp[i] = fmin(dp[i], dp[j] + pow(cost(j + 1, i), P));
        }
    }

    if (dp[N] > 1e18) {
        printf("Too hard to arrange\n");
        return;
    }

    printf("%lld\n", dp[N]);

    int i = N;
    while (i > 0) {
        int j = 0;
        for (; j < i; j++) {
            if (dp[i] == dp[j] + pow(cost(j + 1, i), P)) break;
        }
        for (int k = j + 1; k <= i; k++) {
            printf("%s", sentences[k - 1]);
            if (k != i) printf(" ");
        }
        printf("\n");
        i = j;
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d %d", &N, &L, &P);
        for (int i = 0; i < N; i++) {
            scanf("%s", sentences[i]);
        }
        solve();
        printf("--------------------\n");
    }
    return 0;
}