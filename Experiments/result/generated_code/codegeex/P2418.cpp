#include <stdio.h>
#include <stdlib.h>

#define MAXN 500005

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    int students[MAXN];
    for (int i = 1; i <= N; i++) {
        scanf("%d", &students[i]);
    }

    int dp[MAXN];
    int count1, count2;
    count1 = count2 = 0;

    for (int i = 1; i <= N; i++) {
        if (students[i] == 1) {
            count1++;
        } else {
            count2++;
        }

        dp[i] = i;
        for (int j = 1; j < i; j++) {
            if (abs(count1 - count2) <= M) {
                dp[i] = dp[i] < dp[j] + 1 ? dp[i] : dp[j] + 1;
            }
        }
    }

    printf("%d\n", dp[N]);

    return 0;
}