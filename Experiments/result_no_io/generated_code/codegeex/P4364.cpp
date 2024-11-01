#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

int cmp(const void *a, const void *b) {
    return *(int*)b - *(int*)a;
}

int main() {
    int n;
    double k;
    scanf("%d %lf", &n, &k);
    int d[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &d[i]);
    }

    qsort(d, n, sizeof(int), cmp);

    int ans[n];
    for (int i = 0; i < n; i++) {
        ans[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int p = i;
        while (p >= 0 && d[p] == d[i]) {
            p--;
        }
        p++;
        int q = (int)(i / k);
        while (q >= 0 && d[q] >= d[i]) {
            if (ans[q] == -1 || d[p] > d[ans[q]]) {
                ans[q] = p;
            }
            q = (int)(q / k);
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", d[ans[i]]);
    }
    printf("\n");

    return 0;
}