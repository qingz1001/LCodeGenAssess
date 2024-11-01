#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int cmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

ll min(ll a, ll b) {
    return a < b ? a : b;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        int *w = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            scanf("%d", &w[i]);
        }
        qsort(w, n, sizeof(int), cmp);

        ll ans = 0;
        for (int i = 0; i < n - 1; i++) {
            ans += w[i] + 2 * (w[i] + w[i + 1]) + w[i + 1];
        }

        printf("%lld\n", ans);
        free(w);
    }
    return 0;
}