#include <stdio.h>
#include <stdbool.h>

int main() {
    int n;
    scanf("%d", &n);

    int a[n+1];
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    int count[n+1];
    for (int i = 1; i <= n; i++) {
        count[i] = 0;
    }

    for (int i = 1; i <= n; i++) {
        count[a[i]]++;
    }

    int result = 0;
    for (int i = 1; i <= n; i++) {
        if (count[i] == 0) {
            result++;
        }
    }

    printf("%d\n", result);
    return 0;
}