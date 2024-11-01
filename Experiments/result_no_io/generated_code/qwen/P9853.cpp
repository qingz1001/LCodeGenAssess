#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005
#define MAXQ 200005
#define MAXR 2000000000

typedef struct {
    int a, b, c;
} Equation;

Equation equations[MAXN];
int solutions[MAXR + 1];

int main() {
    int n, Q;
    scanf("%d %d", &n, &Q);

    for (int i = 0; i < n; ++i) {
        scanf("%d %d %d", &equations[i].a, &equations[i].b, &equations[i].c);
        if (equations[i].a > 0) {
            int start = (equations[i].c - equations[i].b + equations[i].a - 1) / equations[i].a;
            solutions[start]++;
        } else {
            int end = (equations[i].c - equations[i].b) / -equations[i].a;
            solutions[end]++;
        }
    }

    for (int i = 1; i <= MAXR; ++i) {
        solutions[i] += solutions[i - 1];
    }

    while (Q--) {
        int L, R;
        scanf("%d %d", &L, &R);
        printf("%d\n", solutions[R] - solutions[L - 1]);
    }

    return 0;
}