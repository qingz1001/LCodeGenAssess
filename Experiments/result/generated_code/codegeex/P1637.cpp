#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int a[30001];
    int b[100001];
    int ans = 0;

    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    for (int i = 1; i <= n; i++) {
        b[a[i]]++;
    }

    for (int i = 1; i <= 100000; i++) {
        b[i] += b[i - 1];
    }

    for (int i = 1; i <= n; i++) {
        ans += b[a[i] - 1];
    }

    printf("%d", ans);

    return 0;
}