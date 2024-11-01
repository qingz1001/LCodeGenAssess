#include <stdio.h>
#include <stdlib.h>

#define MAXN 10005

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n;
    scanf("%d", &n);
    int a[MAXN];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    qsort(a, n, sizeof(int), compare);

    int result = 0;
    while (n > 1) {
        int x = a[0];
        int y = a[1];
        result += x + y;
        a[0] = x + y;
        for (int i = 1; i < n - 1; i++) {
            a[i] = a[i + 1];
        }
        n--;
        qsort(a, n, sizeof(int), compare);
    }

    printf("%d\n", result);
    return 0;
}