#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#define MAX_T 10
#define MAX_N 100000
#define MAX_L 3000000
#define MAX_P 10
#define INF 1e18

typedef long long ll;

int T, N, L, P;
char sentences[MAX_N][31];
ll dp[MAX_N];
int path[MAX_N];

ll power(ll x, int p) {
    ll res = 1;
    while (p--) res *= x;
    return res;
}

ll cost(int i, int j) {
    int len = 0;
    for (int k = i; k <= j; k++) len += strlen(sentences[k]) + (k != j);
    len -= (j - i + 1);
    if (len > L) return INF;
    return power(abs(L - len), P);
}

void solve() {
    for (int i = 0; i < N; i++) dp[i] = INF;
    dp[0] = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {
            ll c = cost(i, j);
            if (c == INF) break;
            if (dp[i] + c < dp[j + 1]) {
                dp[j + 1] = dp[i] + c;
                path[j + 1] = i;
            }
        }
    }
}

void print_solution(int n) {
    if (n == 0) return;
    print_solution(path[n]);
    for (int i = path[n]; i < n; i++) {
        printf("%s", sentences[i]);
        if (i < n - 1) printf(" ");
    }
    printf("\n");
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d %d", &N, &L, &P);
        for (int i = 0; i < N; i++) scanf("%s", sentences[i]);
        solve();
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