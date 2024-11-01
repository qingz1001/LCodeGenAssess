#include <stdio.h>

long long catalan(int n) {
    if (n <= 1) return 1;
    long long res = 0;
    for (int i = 0; i < n; i++) {
        res += catalan(i) * catalan(n - i - 1);
    }
    return res;
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%lld\n", catalan(n));
    return 0;
}