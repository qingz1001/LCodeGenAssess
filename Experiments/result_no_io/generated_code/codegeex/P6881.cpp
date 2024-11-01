#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

const int MAXN = 200005;
const int MAXQ = 200005;

int n, q;
int s[MAXN];
int t[MAXQ], l[MAXQ], r[MAXQ];

int main() {
    // 读取输入
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &s[i]);
    }
    for (int i = 0; i < q; i++) {
        scanf("%d %d %d", &t[i], &l[i], &r[i]);
    }

    // 对每个操作计算代价
    for (int i = 0; i < q; i++) {
        ll cost = 0;
        for (int j = l[i]; j <= r[i]; j++) {
            int max_s = 0;
            for (int k = 1; k <= t[i]; k++) {
                max_s = (max_s > s[j]) ? max_s : s[j];
                s[j] = max_s;
            }
            cost += max_s;
        }
        printf("%lld\n", cost);
    }

    return 0;
}