#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

const int MAXN = 400005;
const int MAXLOG = 20;

int n, q;
int a[MAXN];

int main() {
    // 读取序列长度和操作个数
    scanf("%d%d", &n, &q);

    // 读取初始序列
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    // 处理每个操作
    for (int i = 0; i < q; i++) {
        int op;
        scanf("%d", &op);

        if (op == 1) {
            // 区间加操作
            int l, r, x;
            scanf("%d%d%d", &l, &r, &x);
            for (int j = l; j <= r; j++) {
                a[j] += x;
            }
        } else if (op == 2) {
            // 区间最大子段和查询
            int l, r;
            scanf("%d%d", &l, &r);
            ll max_sum = -1e18;
            ll current_sum = 0;

            for (int j = l; j <= r; j++) {
                current_sum = (current_sum + a[j] > a[j]) ? (current_sum + a[j]) : a[j];
                max_sum = (current_sum > max_sum) ? current_sum : max_sum;
            }

            printf("%lld\n", max_sum);
        }
    }

    return 0;
}