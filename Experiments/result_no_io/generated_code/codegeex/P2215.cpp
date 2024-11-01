#include <stdio.h>
#include <stdlib.h>

#define MAXN 10010

int a[MAXN], dp[MAXN], prev[MAXN];

int cmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

void print_sequence(int length) {
    if (length == 0) return;
    print_sequence(prev[length]);
    printf("%d ", a[length]);
}

int main() {
    int n, m, l;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        dp[i] = 1;
        prev[i] = 0;
    }
    qsort(a + 1, n, sizeof(int), cmp);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            if (a[j] < a[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                prev[i] = j;
            }
        }
    }
    scanf("%d", &m);
    while (m--) {
        scanf("%d", &l);
        if (dp[n] < l) {
            printf("Impossible\n");
        } else {
            for (int i = n; i > 0; i--) {
                if (dp[i] == l) {
                    print_sequence(i);
                    printf("\n");
                    break;
                }
            }
        }
    }
    return 0;
}