#include <stdio.h>
#include <stdlib.h>

#define MAX_M 250
#define MAX_N 25

typedef struct {
    int a, b;
} Pair;

int cmp(const void *a, const void *b) {
    Pair *p1 = (Pair *)a;
    Pair *p2 = (Pair *)b;
    if (p1->b != p2->b) return p1->b - p2->b;
    return p1->a - p2->a;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int max_value = 2 * m * m;
    int *is_double_square = (int *)calloc(max_value + 1, sizeof(int));
    for (int p = 0; p <= m; p++) {
        for (int q = 0; q <= m; q++) {
            is_double_square[p * p + q * q] = 1;
        }
    }

    Pair *results = (Pair *)malloc(10000 * sizeof(Pair));
    int result_count = 0;

    for (int a = 0; a <= max_value; a++) {
        if (!is_double_square[a]) continue;
        for (int b = 1; a + (n - 1) * b <= max_value; b++) {
            int valid = 1;
            for (int k = 0; k < n; k++) {
                if (!is_double_square[a + k * b]) {
                    valid = 0;
                    break;
                }
            }
            if (valid) {
                results[result_count].a = a;
                results[result_count].b = b;
                result_count++;
            }
        }
    }

    qsort(results, result_count, sizeof(Pair), cmp);

    if (result_count == 0) {
        printf("NONE\n");
    } else {
        for (int i = 0; i < result_count; i++) {
            printf("%d %d\n", results[i].a, results[i].b);
        }
    }

    free(is_double_square);
    free(results);

    return 0;
}