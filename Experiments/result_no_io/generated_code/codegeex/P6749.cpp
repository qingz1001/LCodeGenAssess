#include <stdio.h>
#include <stdlib.h>

#define MAXN 30001

long long tree[MAXN * 3]; // 树状数组，用于维护逆序对
int n, m, a[MAXN]; // 序列长度、操作次数和序列

// 树状数组的更新操作
void update(int i, int delta) {
    while (i <= n) {
        tree[i] += delta;
        i += i & -i;
    }
}

// 树状数组的查询操作
long long query(int i) {
    long long sum = 0;
    while (i > 0) {
        sum += tree[i];
        i -= i & -i;
    }
    return sum;
}

// 二分查找确定等差数列的起始位置
int find_start(int l, int r, int x) {
    int mid, ans = r + 1;
    while (l <= r) {
        mid = (l + r) / 2;
        if (a[mid] >= x) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return ans;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        update(i, 1); // 初始化树状数组
    }

    for (int i = 0; i < m; i++) {
        int op, l, r, x;
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d%d%d", &l, &r, &x);
            int start = find_start(l, r, x);
            for (int j = start; j <= r; j++) {
                update(j, -1); // 删除原来的元素
            }
            for (int j = start; j <= r; j++) {
                a[j] = x + j - start; // 更新序列
                update(j, 1); // 插入新的元素
            }
        } else {
            printf("%lld\n", query(n) - query(l - 1)); // 查询逆序对个数
        }
    }
    return 0;
}