#include <stdio.h>
#include <math.h>

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        int ans = 0;
        for (int i = 0; i * i <= n; i++) {
            for (int j = 0; j * j <= n - i * i; j++) {
                for (int k = 0; k * k <= n - i * i - j * j; k++) {
                    int l = sqrt(n - i * i - j * j - k * k);
                    if (l * l == n - i * i - j * j - k * k) {
                        ans++;
                    }
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}