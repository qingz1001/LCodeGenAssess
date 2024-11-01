#include <stdio.h>
#include <string.h>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int a[n+1];
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    int cost = 0;
    for (int i = 1; i <= k; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (a[i] == a[j]) {
                // Swap a[i] and a[j]
                int temp = a[i];
                a[i] = a[j];
                a[j] = temp;
                cost++;
            }
        }
    }

    for (int i = 1; i <= k; i++) {
        if (a[i] == a[i+1]) {
            printf("-1\n");
            return 0;
        }
    }

    printf("%d\n", cost);
    return 0;
}