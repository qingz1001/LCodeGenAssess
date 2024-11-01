#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int p[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }

    int merge_count = 0;
    for (int i = 1; i < n - 1; i++) {
        if (p[i] > p[i + 1]) {
            merge_count++;
            p[i + 1] += p[i];
        }
    }

    printf("%d\n", merge_count);

    return 0;
}