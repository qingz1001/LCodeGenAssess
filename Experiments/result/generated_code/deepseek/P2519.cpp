#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005

typedef struct {
    int a, b;
} Statement;

Statement statements[MAXN];
int dp[MAXN];

int cmp(const void *a, const void *b) {
    Statement *sa = (Statement *)a;
    Statement *sb = (Statement *)b;
    if (sa->a == sb->a) return sa->b - sb->b;
    return sa->a - sb->a;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &statements[i].a, &statements[i].b);
    }

    qsort(statements, n, sizeof(Statement), cmp);

    memset(dp, 0, sizeof(dp));
    int max_dp = 0;

    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = i - 1; j >= 0; j--) {
            if (statements[j].a <= statements[i].a && statements[j].b <= statements[i].b) {
                count++;
            }
        }
        dp[i] = count + 1;
        if (dp[i] > max_dp) {
            max_dp = dp[i];
        }
    }

    printf("%d\n", n - max_dp);

    return 0;
}