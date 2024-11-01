#include <stdio.h>
#include <limits.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    for (int i = 0; i < n; i++) {
        int min = INT_MAX;
        for (int j = i - m; j < i; j++) {
            if (j >= 0 && a[j] < min) {
                min = a[j];
            }
        }
        if (i == 0) {
            printf("0\n");
        } else {
            printf("%d\n", min);
        }
    }

    return 0;
}