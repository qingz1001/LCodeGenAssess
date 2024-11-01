#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int n;
    scanf("%d", &n);
    int *a = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    qsort(a, n, sizeof(int), compare);

    int max_min_group_size = 0;
    int i = 0;
    while (i < n) {
        int j = i;
        while (j < n && a[j] == a[i]) {
            j++;
        }
        int k = j;
        while (k < n && a[k] == a[j] + (k - j)) {
            k++;
        }
        int group_size = k - i;
        if (group_size > max_min_group_size) {
            max_min_group_size = group_size;
        }
        i = j;
    }

    printf("%d\n", max_min_group_size);

    free(a);
    return 0;
}