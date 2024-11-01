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

ll fast_pow(ll base, int exp) {
    ll result = 1;
    while (exp) {
        if (exp & 1) result = result * base;
        base = base * base;
        exp >>= 1;
    }
    return result;
}

ll cost(int i, int j) {
    int len = 0;
    for (int k = i; k <= j; k++) {
        len += strlen(sentences[k]);
        if (k < j) len++; // space between sentences
    }
    int diff = abs(len - L);
    return fast_pow(diff, P);
}

void solve() {
    for (int i = 0; i < N; i++) {
        dp[i] = INF;
        path[i] = -1;
    }
    dp[0] = cost(0, 0);
    for (int i = 1; i < N; i++) {
        for (int j = 0; j < i; j++) {
            ll c = cost(j + 1, i);
            if (dp[j] + c < dp[i]) {
                dp[i] = dp[j] + c;
                path[i] = j;
            }
        }
    }
}

void print_solution(int n) {
    if (n == -1) return;
    print_solution(path[n]);
    for (int i = path[n] + 1; i <= n; i++) {
        printf("%s", sentences[i]);
        if (i < n) printf(" ");
    }
    printf("\n");
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d %d", &N, &L, &P);
        for (int i = 0; i < N; i++) {
            scanf("%s", sentences[i]);
        }
        solve();
        if (dp[N - 1] > INF) {
            printf("Too hard to arrange\n");
        } else {
            printf("%lld\n", dp[N - 1]);
            print_solution(N - 1);
        }
        printf("--------------------\n");
    }
    return 0;
}