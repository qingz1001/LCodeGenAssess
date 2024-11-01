#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define EPS 1e-9

typedef struct {
    double data[MAXN];
    int size;
} Array;

void initArray(Array *arr) {
    arr->size = 0;
}

void pushBack(Array *arr, double value) {
    arr->data[arr->size++] = value;
}

double getAverage(const Array *arr) {
    double sum = 0;
    for (int i = 0; i < arr->size; ++i) {
        sum += arr->data[i];
    }
    return sum / arr->size;
}

double getVariance(const Array *arr) {
    double avg = getAverage(arr);
    double sumOfSquares = 0;
    for (int i = 0; i < arr->size; ++i) {
        sumOfSquares += (arr->data[i] - avg) * (arr->data[i] - avg);
    }
    return sumOfSquares / arr->size;
}

void updateRange(Array *arr, int start, int end, double value) {
    for (int i = start; i <= end; ++i) {
        arr->data[i] += value;
    }
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    Array arr;
    initArray(&arr);

    for (int i = 0; i < N; ++i) {
        double num;
        scanf("%lf", &num);
        pushBack(&arr, num);
    }

    for (int i = 0; i < M; ++i) {
        int op, x, y;
        double k;
        scanf("%d %d %d", &op, &x, &y);
        if (op == 1) {
            scanf("%lf", &k);
            updateRange(&arr, x - 1, y - 1, k);
        } else if (op == 2 || op == 3) {
            double result;
            if (op == 2) {
                result = getAverage(&arr);
            } else {
                result = getVariance(&arr);
            }
            printf("%.4f\n", result);
        }
    }

    return 0;
}