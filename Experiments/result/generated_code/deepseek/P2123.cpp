#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    long long a;
    long long b;
} Minister;

int compare(const void *a, const void *b) {
    Minister *m1 = (Minister *)a;
    Minister *m2 = (Minister *)b;
    return (m1->a + m1->b) - (m2->a + m2->b);
}

long long calculateMaxBonus(Minister *ministers, int n) {
    qsort(ministers, n, sizeof(Minister), compare);

    long long maxBonus = 0;
    long long sumA = 0;

    for (int i = 0; i < n; i++) {
        long long currentBonus = sumA + ministers[i].a + ministers[i].b;
        if (currentBonus > maxBonus) {
            maxBonus = currentBonus;
        }
        sumA += ministers[i].a;
    }

    return maxBonus;
}

int main() {
    int T;
    scanf("%d", &T);

    for (int t = 0; t < T; t++) {
        int n;
        scanf("%d", &n);

        Minister *ministers = (Minister *)malloc(n * sizeof(Minister));
        for (int i = 0; i < n; i++) {
            scanf("%lld %lld", &ministers[i].a, &ministers[i].b);
        }

        long long result = calculateMaxBonus(ministers, n);
        printf("%lld\n", result);

        free(ministers);
    }

    return 0;
}