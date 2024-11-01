#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int result[n];
    for (int i = 0; i < n; i++) {
        result[i] = 0;
        for (int j = 0; j < i; j++) {
            if (a[j] > a[i]) {
                result[i]++;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", result[i]);
    }
    return 0;
}