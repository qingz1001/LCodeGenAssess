#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_N 100005
#define MAX_LEN 35
#define INF 1e18

char sentences[MAX_N][MAX_LEN];
int lengths[MAX_N];
long long dp[MAX_N];
int prev[MAX_N];

long long badness(int i, int j, int L, int P) {
    long long spaces = j - i;
    long long chars = 0;
    for (int k = i; k <= j; k++) {
        chars += lengths[k];
    }
    long long length = chars + spaces;
    if (length > L) return INF;
    return pow(labs(L - length), P);
}

void print_solution(int n) {
    if (n == 0) return;
    print_solution(prev[n]);
    for (int i = prev[n] + 1; i <= n; i++) {
        if (i > prev[n] + 1) printf(" ");
        printf("%s", sentences[i]);
    }
    printf("\n");
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int N, L, P;
        scanf("%d %d %d", &N, &L, &P);

        for (int i = 1; i <= N; i++) {
            scanf("%s", sentences[i]);
            lengths[i] = strlen(sentences[i]);
        }

        dp[0] = 0;
        for (int i = 1; i <= N; i++) {
            dp[i] = INF;
            for (int j = i; j >= 1 && i - j <= 100; j--) {
                long long cost = dp[j-1] + badness(j, i, L, P);
                if (cost < dp[i]) {
                    dp[i] = cost;
                    prev[i] = j - 1;
                }
            }
        }

        if (dp[N] > INF) {
            printf("Too hard to arrange\n");
        } else {
            printf("%lld\n", dp[N]);
            print_solution(N);
        }

        printf("--------------------\n");
    }

    return 0;
}