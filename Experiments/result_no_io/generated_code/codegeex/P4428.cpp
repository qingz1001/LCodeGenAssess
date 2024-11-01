#include <stdio.h>
#include <string.h>

typedef long long ll;

const int MAXN = 100005;
const int MAXM = 100005;

int n, m;
int a[MAXN];
int bit[MAXN];
ll ans[MAXN];

// 树状数组的更新操作
void update(int x, int val) {
    while (x <= n) {
        bit[x] += val;
        x += x & -x;
    }
}

// 树状数组的查询操作
ll query(int x) {
    ll sum = 0;
    while (x > 0) {
        sum += bit[x];
        x -= x & -x;
    }
    return sum;
}

// 计算区间[l, r]内满足条件的子串数量
ll calculate(int l, int r) {
    int count0 = 0, count1 = 0;
    for (int i = l; i <= r; i++) {
        if (a[i] == 0) count0++;
        else count1++;
    }
    ll result = 0;
    for (int i = 0; i <= count0; i += 3) {
        result += (count0 - i + 1) * (count1 + 1);
    }
    return result;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    scanf("%d", &m);

    // 初始化答案数组
    for (int i = 1; i <= n; i++) {
        ans[i] = calculate(1, i);
    }

    // 处理每个操作
    for (int i = 1; i <= m; i++) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int pos;
            scanf("%d", &pos);
            a[pos] ^= 1; // 修改操作
            // 更新受影响的区间答案
            ans[pos] = calculate(1, pos);
            for (int j = pos + 1; j <= n; j++) {
                ans[j] = calculate(1, j);
            }
        } else if (op == 2) {
            int l, r;
            scanf("%d%d", &l, &r);
            printf("%lld\n", ans[r] - ans[l - 1]);
        }
    }

    return 0;
}