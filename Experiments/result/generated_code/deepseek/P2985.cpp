#include <stdio.h>
#include <stdlib.h>

#define MAXN 50000
#define MAXD 50000

int N, D;
int H[MAXN];
int schedule[MAXN];

int check(long long min_happiness) {
    long long happiness = 0;
    int day = 1;
    for (int i = 0; i < N; i++) {
        if (happiness < min_happiness) {
            happiness += H[i];
            schedule[i] = day;
        } else {
            day++;
            happiness = H[i];
            schedule[i] = day;
        }
        if (day > D) return 0;
        happiness /= 2;
    }
    return 1;
}

int main() {
    scanf("%d %d", &N, &D);
    for (int i = 0; i < N; i++) {
        scanf("%d", &H[i]);
    }

    long long left = 0, right = 1e12;
    long long best = 0;

    while (left <= right) {
        long long mid = (left + right) / 2;
        if (check(mid)) {
            best = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    check(best);

    printf("%lld\n", best);
    for (int i = 0; i < N; i++) {
        printf("%d\n", schedule[i]);
    }

    return 0;
}