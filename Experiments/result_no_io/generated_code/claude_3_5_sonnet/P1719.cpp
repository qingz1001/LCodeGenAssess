#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 120
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int matrix[MAX_N][MAX_N];
int sum[MAX_N][MAX_N];
int n;

int kadane(int* arr, int* start, int* finish, int n) {
    int sum = 0, maxSum = -1e9, i;
    int local_start = 0;

    *finish = -1;

    for (i = 0; i < n; ++i) {
        sum += arr[i];
        if (sum < 0) {
            sum = 0;
            local_start = i + 1;
        } else if (sum > maxSum) {
            maxSum = sum;
            *start = local_start;
            *finish = i;
        }
    }

    if (*finish != -1)
        return maxSum;

    maxSum = arr[0];
    *start = *finish = 0;

    for (i = 1; i < n; i++) {
        if (arr[i] > maxSum) {
            maxSum = arr[i];
            *start = *finish = i;
        }
    }
    return maxSum;
}

int maxSumRectangle() {
    int maxSum = -1e9, finalLeft, finalRight, finalTop, finalBottom;
    int left, right, i, j, sum, start, finish;
    int temp[MAX_N];

    for (left = 0; left < n; ++left) {
        memset(temp, 0, sizeof(temp));
        for (right = left; right < n; ++right) {
            for (i = 0; i < n; ++i)
                temp[i] += sum[i][right] - (left > 0 ? sum[i][left-1] : 0);

            sum = kadane(temp, &start, &finish, n);

            if (sum > maxSum) {
                maxSum = sum;
                finalLeft = left;
                finalRight = right;
                finalTop = start;
                finalBottom = finish;
            }
        }
    }
    return maxSum;
}

int main() {
    int i, j;
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
            sum[i][j] = matrix[i][j];
            if (i > 0) sum[i][j] += sum[i-1][j];
            if (j > 0) sum[i][j] += sum[i][j-1];
            if (i > 0 && j > 0) sum[i][j] -= sum[i-1][j-1];
        }
    }

    printf("%d\n", maxSumRectangle());
    return 0;
}