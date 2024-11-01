#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int a[n];
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }

    for (int i = 0; i < n; ++i) {
        if (i < m) {
            printf("0\n");
        } else {
            int min_val = a[0];
            for (int j = 1; j <= m; ++j) {
                if (a[j] < min_val) {
                    min_val = a[j];
                }
            }
            printf("%d\n", min_val);
        }
    }

    return 0;
}