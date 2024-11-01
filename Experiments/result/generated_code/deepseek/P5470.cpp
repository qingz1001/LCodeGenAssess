#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005
#define MAXK 200005

typedef struct {
    int index;
    long long value;
} Pair;

int cmp(const void *a, const void *b) {
    return ((Pair *)b)->value - ((Pair *)a)->value;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, K, L;
        scanf("%d %d %d", &n, &K, &L);
        long long a[MAXN], b[MAXN];
        Pair sum[MAXN];

        for (int i = 0; i < n; i++) {
            scanf("%lld", &a[i]);
        }
        for (int i = 0; i < n; i++) {
            scanf("%lld", &b[i]);
        }

        for (int i = 0; i < n; i++) {
            sum[i].index = i;
            sum[i].value = a[i] + b[i];
        }

        qsort(sum, n, sizeof(Pair), cmp);

        long long total_sum = 0;
        int common_count = 0;
        int a_count = 0, b_count = 0;
        int selected[MAXN] = {0};

        for (int i = 0; i < K; i++) {
            int idx = sum[i].index;
            total_sum += sum[i].value;
            selected[idx] = 1;
            if (a_count < K) a_count++;
            if (b_count < K) b_count++;
            if (a_count == K && b_count == K) break;
        }

        for (int i = K; i < n; i++) {
            int idx = sum[i].index;
            if (common_count < L) {
                if (selected[idx]) {
                    common_count++;
                } else {
                    if (a_count < K) {
                        total_sum += a[idx];
                        a_count++;
                        selected[idx] = 1;
                    }
                    if (b_count < K) {
                        total_sum += b[idx];
                        b_count++;
                        selected[idx] = 1;
                    }
                }
            } else {
                if (a_count < K) {
                    total_sum += a[idx];
                    a_count++;
                    selected[idx] = 1;
                }
                if (b_count < K) {
                    total_sum += b[idx];
                    b_count++;
                    selected[idx] = 1;
                }
            }
            if (a_count == K && b_count == K) break;
        }

        printf("%lld\n", total_sum);
    }
    return 0;
}