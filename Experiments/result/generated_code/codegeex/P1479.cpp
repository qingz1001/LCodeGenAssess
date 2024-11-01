#include <stdio.h>

int main() {
    int n, ans = 0;
    scanf("%d", &n);

    for (int k = 1; k <= 12; k++) {
        int sum = 0;
        for (int i = 1; i <= n; i++) {
            sum += (i - k + 1) * (n - i + 1);
        }
        if (sum % 2 == 0) {
            ans += sum / 2;
        } else {
            ans += (sum + 1) / 2;
        }
    }

    printf("%d\n", ans);
    return 0;
}