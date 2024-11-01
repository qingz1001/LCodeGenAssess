#include <stdio.h>
#include <stdlib.h>

#define MAXN 100001

int n, m;
int a[MAXN];

// 全部变成0
void zero(int l, int r) {
    for (int i = l; i <= r; i++) {
        a[i] = 0;
    }
}

// 全部变成1
void one(int l, int r) {
    for (int i = l; i <= r; i++) {
        a[i] = 1;
    }
}

// 全部取反
void reverse(int l, int r) {
    for (int i = l; i <= r; i++) {
        a[i] = !a[i];
    }
}

// 询问区间内1的个数
int count(int l, int r) {
    int res = 0;
    for (int i = l; i <= r; i++) {
        if (a[i] == 1) {
            res++;
        }
    }
    return res;
}

// 询问区间内最大连续1的个数
int maxConsecutiveOnes(int l, int r) {
    int res = 0, current = 0;
    for (int i = l; i <= r; i++) {
        if (a[i] == 1) {
            current++;
        } else {
            res = (res > current) ? res : current;
            current = 0;
        }
    }
    res = (res > current) ? res : current;
    return res;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < m; i++) {
        int op, l, r;
        scanf("%d %d %d", &op, &l, &r);
        if (op == 0) {
            zero(l, r);
        } else if (op == 1) {
            one(l, r);
        } else if (op == 2) {
            reverse(l, r);
        } else if (op == 3) {
            printf("%d\n", count(l, r));
        } else if (op == 4) {
            printf("%d\n", maxConsecutiveOnes(l, r));
        }
    }
    return 0;
}