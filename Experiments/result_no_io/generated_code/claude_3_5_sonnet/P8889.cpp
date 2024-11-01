#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 500005

long long a[MAX_N], b[MAX_N];
int cut[MAX_N];

int cmp(const void *a, const void *b) {
    return *(long long*)a - *(long long*)b > 0 ? 1 : -1;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }

    for (int i = 0; i < m; i++) {
        scanf("%lld", &b[i]);
    }

    qsort(b, m, sizeof(long long), cmp);

    memset(cut, 0, sizeof(cut));
    for (int i = 0; i < n; i++) {
        if (bsearch(&a[i], b, m, sizeof(long long), cmp)) {
            cut[i] = 1;
        }
    }

    int segments = 0;
    int in_segment = 0;
    for (int i = 0; i < n; i++) {
        if (cut[i]) {
            if (in_segment) {
                segments++;
                in_segment = 0;
            }
        } else {
            in_segment = 1;
        }
    }
    if (in_segment) {
        segments++;
    }

    printf("%d\n", segments);

    return 0;
}