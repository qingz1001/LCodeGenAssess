#include <stdio.h>

// 计算卡特兰数
long long catalan(int n) {
    if (n == 0 || n == 1) return 1;
    long long cat[n + 1];
    cat[0] = cat[1] = 1;
    for (int i = 2; i <= n; i++) {
        cat[i] = 0;
        for (int j = 0; j < i; j++) {
            cat[i] += cat[j] * cat[i - 1 - j];
        }
    }
    return cat[n];
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%lld\n", catalan(n));
    return 0;
}