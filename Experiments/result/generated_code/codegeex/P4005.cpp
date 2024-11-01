#include <stdio.h>

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        int a[45];
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
        }

        int ans = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                if (a[i] == a[j]) {
                    ans++;
                    break;
                }
            }
        }

        printf("%d\n", ans);
    }
    return 0;
}