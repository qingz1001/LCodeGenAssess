#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005

typedef struct {
    int a, b;
} Person;

Person people[MAXN];
int dp[MAXN];

int cmp(const void *a, const void *b) {
    Person *pa = (Person *)a;
    Person *pb = (Person *)b;
    if (pa->a == pb->a) return pa->b - pb->b;
    return pa->a - pb->a;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &people[i].a, &people[i].b);
    }

    qsort(people, n, sizeof(Person), cmp);

    memset(dp, 0, sizeof(dp));
    int max_dp = 0;

    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = i - 1; j >= 0; j--) {
            if (people[j].a == people[i].a && people[j].b == people[i].b) {
                count++;
            } else {
                break;
            }
        }
        dp[i] = count + 1;
        if (i > 0) {
            dp[i] = dp[i - 1] > dp[i] ? dp[i - 1] : dp[i];
        }
        max_dp = max_dp > dp[i] ? max_dp : dp[i];
    }

    printf("%d\n", n - max_dp);

    return 0;
}