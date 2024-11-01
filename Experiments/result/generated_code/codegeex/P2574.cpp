#include <stdio.h>
#include <string.h>

#define MAXN 200005

int n, m;
char s[MAXN];
int bit[MAXN];

// 更新树状数组
void update(int idx, int delta) {
    while (idx <= n) {
        bit[idx] += delta;
        idx += idx & -idx;
    }
}

// 查询树状数组
int query(int idx) {
    int sum = 0;
    while (idx > 0) {
        sum += bit[idx];
        idx -= idx & -idx;
    }
    return sum;
}

int main() {
    // 读取输入
    scanf("%d %d", &n, &m);
    scanf("%s", s);

    // 初始化树状数组
    memset(bit, 0, sizeof(bit));
    for (int i = 1; i <= n; i++) {
        update(i, s[i - 1] - '0');
    }

    // 处理操作
    for (int i = 0; i < m; i++) {
        int op, l, r;
        scanf("%d %d %d", &op, &l, &r);

        if (op == 0) {
            // 翻转区间 [l, r]
            int ones_before = query(l - 1);
            int ones_after = query(r);
            int zeros_before = (l - 1) - ones_before;
            int zeros_after = r - ones_after;

            update(l, zeros_before - ones_before);
            update(r + 1, ones_after - zeros_after);
        } else if (op == 1) {
            // 查询区间 [l, r] 内 1 的个数
            int ones = query(r) - query(l - 1);
            printf("%d\n", ones);
        }
    }

    return 0;
}