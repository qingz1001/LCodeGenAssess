#include <stdio.h>
#include <stdlib.h>

// 检查给定威力值 p 是否可以消灭所有怪物
int check(int p, int n, int k, long long *m) {
    long long damage = 0;
    for (int i = 0; i < n; i++) {
        if (m[i] <= 0) continue;
        if (i > 0) {
            damage += p - (i * i);
        }
        if (damage >= m[i]) {
            damage -= m[i];
            m[i] = 0;
        } else {
            m[i] -= damage;
            damage = 0;
            if (k == 1) return 0;
            k--;
        }
    }
    return k == 0;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    long long *m = (long long *)malloc(n * sizeof(long long));
    for (int i = 0; i < n; i++) {
        scanf("%lld", &m[i]);
    }

    int left = 0, right = 0;
    for (int i = 0; i < n; i++) {
        right += m[i];
    }
    right = (right + k - 1) / k;

    while (left < right) {
        int mid = (left + right) / 2;
        if (check(mid, n, k, m)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    printf("%d\n", left);
    free(m);
    return 0;
}