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

    int count = 0;
    int double_squares[MAX_M * MAX_M];
    for (int p = 0; p <= m; p++) {
        for (int q = 0; q <= m; q++) {
            double_squares[count++] = p * p + q * q;
        }
    }

    qsort(double_squares, count, sizeof(int), cmp);

    Pair results[10000];
    int result_count = 0;

    for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count; j++) {
            int a = double_squares[i];
            int b = double_squares[j] - double_squares[i];
            int valid = 1;
            for (int k = 1; k < n; k++) {
                if (b == 0 || a + k * b > 2 * m * m) {
                    valid = 0;
                    break;
                }
                int found = 0;
                for (int l = 0; l < count; l++) {
                    if (double_squares[l] == a + k * b) {
                        found = 1;
                        break;
                    }
                }
                if (!found) {
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

    if (result_count == 0) {
        printf("NONE\n");
    } else {
        qsort(results, result_count, sizeof(Pair), cmp);
        for (int i = 0; i < result_count; i++) {
            printf("%d %d\n", results[i].a, results[i].b);
        }
    }

    return 0;
}