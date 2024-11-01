#include <stdio.h>

// 计算组合数 C(n, k)
int combination(int n, int k) {
    if (k > n) return 0;
    if (k == 0 || k == n) return 1;
    return combination(n - 1, k - 1) + combination(n - 1, k);
}

// 计算斯特林数 S(n, r)
int stirling(int n, int r) {
    if (r == 0 && n == 0) return 1;
    if (r == 0 || n == 0) return 0;
    return r * stirling(n - 1, r) + stirling(n - 1, r - 1);
}

int main() {
    int n, r;
    scanf("%d %d", &n, &r);

    // 计算斯特林数 S(n, r) 乘以 r!
    int result = stirling(n, r);
    for (int i = 1; i <= r; i++) {
        result *= i;
    }

    printf("%d\n", result);
    return 0;
}