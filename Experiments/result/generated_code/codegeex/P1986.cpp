#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    int a[5001], b[5001], c[5001], cnt[30001] = {0};
    int i, j, min, ans = 0;
    
    for (i = 1; i <= m; i++) {
        scanf("%d %d %d", &a[i], &b[i], &c[i]);
        for (j = a[i]; j <= b[i]; j++) {
            cnt[j]++;
        }
    }
    
    for (i = 1; i <= n; i++) {
        if (cnt[i] > 0) {
            min = cnt[i];
            for (j = 1; j <= m; j++) {
                if (a[j] <= i && i <= b[j] && cnt[i] < c[j]) {
                    min = c[j];
                    break;
                }
            }
            ans += min;
        }
    }
    
    printf("%d\n", ans);
    return 0;
}