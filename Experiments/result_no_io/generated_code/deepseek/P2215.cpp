#include <stdio.h>
#include <stdlib.h>

#define MAXN 10000
#define MAXM 1000

int S[MAXN];
int dp[MAXN];
int prev[MAXN];
int result[MAXN];

int cmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void find_lis(int n) {
    for (int i = 0; i < n; i++) {
        dp[i] = 1;
        prev[i] = -1;
        for (int j = 0; j < i; j++) {
            if (S[j] < S[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                prev[i] = j;
            }
        }
    }
}

void print_lis(int n, int L) {
    int max_len = 0, max_index = -1;
    for (int i = 0; i < n; i++) {
        if (dp[i] > max_len) {
            max_len = dp[i];
            max_index = i;
        }
    }

    if (max_len < L) {
        printf("Impossible\n");
        return;
    }

    int len = max_len;
    int index = max_index;
    while (len > 0) {
        result[len - 1] = S[index];
        index = prev[index];
        len--;
    }

    for (int i = 0; i < L; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
}

int main() {
    int N, M;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &S[i]);
    }

    find_lis(N);

    scanf("%d", &M);
    for (int i = 0; i < M; i++) {
        int L;
        scanf("%d", &L);
        print_lis(N, L);
    }

    return 0;
}