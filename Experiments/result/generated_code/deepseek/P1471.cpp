#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void update(double *arr, int x, int y, double k, int n) {
    for (int i = x - 1; i < y; i++) {
        arr[i] += k;
    }
}

double average(double *arr, int x, int y) {
    double sum = 0;
    for (int i = x - 1; i < y; i++) {
        sum += arr[i];
    }
    return sum / (y - x + 1);
}

double variance(double *arr, int x, int y) {
    double avg = average(arr, x, y);
    double sum = 0;
    for (int i = x - 1; i < y; i++) {
        sum += (arr[i] - avg) * (arr[i] - avg);
    }
    return sum / (y - x + 1);
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    double *arr = (double *)malloc(N * sizeof(double));
    for (int i = 0; i < N; i++) {
        scanf("%lf", &arr[i]);
    }

    for (int i = 0; i < M; i++) {
        int op, x, y;
        double k;
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d %d %lf", &x, &y, &k);
            update(arr, x, y, k, N);
        } else if (op == 2) {
            scanf("%d %d", &x, &y);
            printf("%.4f\n", average(arr, x, y));
        } else if (op == 3) {
            scanf("%d %d", &x, &y);
            printf("%.4f\n", variance(arr, x, y));
        }
    }

    free(arr);
    return 0;
}