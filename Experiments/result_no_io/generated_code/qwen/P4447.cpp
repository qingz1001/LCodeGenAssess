#include <stdio.h>
#include <stdlib.h>

#define MAXN 100000

int main() {
    int n;
    scanf("%d", &n);
    int a[MAXN];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    // Sort the array
    qsort(a, n, sizeof(int), (int (*)(const void *, const void *))strcmp);

    int min_group_size = 1;
    int current_group_size = 1;

    for (int i = 1; i < n; i++) {
        if (a[i] == a[i - 1]) {
            continue;
        }
        if (a[i] != a[i - 1] + 1) {
            min_group_size = fmax(min_group_size, current_group_size);
            current_group_size = 0;
        }
        current_group_size++;
    }
    min_group_size = fmax(min_group_size, current_group_size);

    printf("%d\n", min_group_size);

    return 0;
}