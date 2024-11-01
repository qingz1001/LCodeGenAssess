#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPS 1e-9

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

double calculate_variance(int *arr, int size, double mean) {
    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum += pow(arr[i] - mean, 2);
    }
    return sqrt(sum / size);
}

void assign_groups(int *arr, int n, int m, int group_size[], double *group_sums) {
    for (int i = 0; i < n; i++) {
        int min_index = 0;
        for (int j = 1; j < m; j++) {
            if (group_sums[j] < group_sums[min_index]) {
                min_index = j;
            }
        }
        arr[i] = min_index;
        group_sums[min_index] += arr[i];
        group_size[min_index]++;
    }
}

double find_min_variance(int *arr, int n, int m) {
    qsort(arr, n, sizeof(int), compare);

    double min_variance = 1e9;
    for (int k = 1; k <= m; k++) {
        int group_size[m];
        double group_sums[m];
        for (int i = 0; i < m; i++) {
            group_size[i] = 0;
            group_sums[i] = 0;
        }

        assign_groups(arr, n, k, group_size, group_sums);

        double total_sum = 0;
        for (int i = 0; i < m; i++) {
            total_sum += group_sums[i];
        }
        double mean = total_sum / k;

        double variance = calculate_variance(group_sums, m, mean);
        if (variance < min_variance) {
            min_variance = variance;
        }
    }

    return min_variance;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    double result = find_min_variance(arr, n, m);
    printf("%.2f\n", result);

    return 0;
}