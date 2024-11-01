#include <stdio.h>
#include <stdlib.h>

#define MAXN 50005
#define MAXD 50005

int N, D;
int H[MAXN];
int ans[MAXN];
long long sum[MAXN];

int check(long long x) {
    int day = 1, i = 1;
    long long cur = 0;
    while (day <= D && i <= N) {
        if (cur < x) {
            cur += H[i];
            ans[i] = day;
            i++;
        } else {
            cur /= 2;
            day++;
        }
    }
    while (day <= D) {
        if (cur < x) return 0;
        cur /= 2;
        day++;
    }
    return i > N;
}

int main() {
    scanf("%d %d", &N, &D);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &H[i]);
        sum[i] = sum[i-1] + H[i];
    }

    long long l = 0, r = sum[N], mid;
    while (l < r) {
        mid = (l + r + 1) / 2;
        if (check(mid)) l = mid;
        else r = mid - 1;
    }

    check(l);
    printf("%lld\n", l);
    for (int i = 1; i <= N; i++) {
        printf("%d\n", ans[i]);
    }

    return 0;
}