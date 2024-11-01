#include <stdio.h>

int main() {
    int n, ans = 1;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        ans *= (2 * i - 1);
    }
    printf("%d\n", ans);
    return 0;
}