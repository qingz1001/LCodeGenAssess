#include <stdio.h>
#include <stdlib.h>

#define MAXN 20001

typedef struct {
    long long a;
    long long b;
} Pair;

int compare(const void *a, const void *b) {
    Pair *p1 = (Pair *)a;
    Pair *p2 = (Pair *)b;
    if (p1->a + p1->b > p2->a + p2->b) {
        return -1;
    } else if (p1->a + p1->b < p2->a + p2->b) {
        return 1;
    } else {
        if (p1->a > p2->a) {
            return -1;
        } else if (p1->a < p2->a) {
            return 1;
        } else {
            return 0;
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        Pair pairs[MAXN];
        for (int i = 0; i < n; i++) {
            scanf("%lld %lld", &pairs[i].a, &pairs[i].b);
        }
        qsort(pairs, n, sizeof(Pair), compare);
        long long sum = 0, max = 0;
        for (int i = 0; i < n; i++) {
            sum += pairs[i].a;
            max = (max > sum) ? max : sum;
        }
        printf("%lld\n", max + pairs[n-1].b);
    }
    return 0;
}