#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define EPS 1e-9

typedef struct {
    double data[MAXN];
    int size;
    double sum, sum_sq;
} Array;

void initArray(Array *arr, int n) {
    arr->size = n;
    for (int i = 0; i < n; i++) {
        scanf("%lf", &arr->data[i]);
        arr->sum += arr->data[i];
        arr->sum_sq += arr->data[i] * arr->data[i];
    }
}

double getMean(Array *arr, int start, int end) {
    return (arr->sum / arr->size);
}

double getVariance(Array *arr, int start, int end) {
    double mean = getMean(arr, start, end);
    double variance = 0;
    for (int i = start; i <= end; i++) {
        variance += (arr->data[i] - mean) * (arr->data[i] - mean);
    }
    variance /= arr->size;
    return variance;
}

void updateRange(Array *arr, int start, int end, double k) {
    for (int i = start; i <= end; i++) {
        arr->data[i] += k;
        arr->sum += k;
        arr->sum_sq += 2 * k * arr->data[i] + k * k;
    }
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    Array arr;
    initArray(&arr, N);

    for (int i = 0; i < M; i++) {
        int op, x, y;
        double k;
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d %d %lf", &x, &y, &k);
            updateRange(&arr, x - 1, y - 1, k);
        } else if (op == 2) {
            scanf("%d %d", &x, &y);
            printf("%.4f\n", getMean(&arr, x - 1, y - 1));
        } else if (op == 3) {
            scanf("%d %d", &x, &y);
            printf("%.4f\n", getVariance(&arr, x - 1, y - 1));
        }
    }

    return 0;
}