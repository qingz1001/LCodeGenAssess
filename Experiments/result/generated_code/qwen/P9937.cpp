#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int compare(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int maxHIndex(int* citations, int n, int l) {
    qsort(citations, n, sizeof(int), compare);
    int h = 0;
    for (int i = 0; i < n && l >= 0; ++i) {
        if (citations[i] > h) {
            h++;
            l--;
        }
    }
    return h;
}

int main() {
    int n, l;
    scanf("%d %d", &n, &l);
    int citations[MAXN];
    for (int i = 0; i < n; ++i) {
        scanf("%d", &citations[i]);
    }
    printf("%d\n", maxHIndex(citations, n, l));
    return 0;
}