#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int *a = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int cost = 0;
    for (int i = 0; i < k - 1; i++) {
        if (a[i] == a[i + 1]) {
            int j = i + 2;
            while (j < n && a[j] == a[i]) {
                j++;
            }
            if (j >= n) {
                printf("-1\n");
                free(a);
                return 0;
            }
            for (; j > i + 1; j--) {
                int temp = a[j];
                a[j] = a[j - 1];
                a[j - 1] = temp;
                cost++;
            }
        }
    }

    printf("%d\n", cost);
    free(a);
    return 0;
}