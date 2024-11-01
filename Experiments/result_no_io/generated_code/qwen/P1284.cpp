#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int main() {
    int n;
    scanf("%d", &n);
    int lengths[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &lengths[i]);
    }

    qsort(lengths, n, sizeof(int), compare);

    for (int i = 0; i < n - 2; i++) {
        if (lengths[i] < lengths[i + 1] + lengths[i + 2]) {
            int a = lengths[i], b = lengths[i + 1], c = lengths[i + 2];
            int s = (a + b + c) / 2;
            long long area = (long long)s * (s - a) * (s - b) * (s - c);
            printf("%lld\n", (area * 100) / s);
            return 0;
        }
    }

    printf("-1\n");
    return 0;
}