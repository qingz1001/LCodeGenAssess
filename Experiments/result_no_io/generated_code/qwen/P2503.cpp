#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 21
#define EPS 1e-9

int n, m;
int a[MAXN];
double sum[MAXN];

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void quicksort(int arr[], int left, int right) {
    if (left >= right) return;
    int pivot = arr[left + rand() % (right - left + 1)];
    int i = left, j = right;
    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i <= j) {
            swap(&arr[i], &arr[j]);
            i++;
            j--;
        }
    }
    quicksort(arr, left, j);
    quicksort(arr, i, right);
}

double calculate_variance(double mean) {
    double var = 0.0;
    for (int i = 0; i < m; i++) {
        var += pow(sum[i] - mean, 2);
    }
    return sqrt(var / m);
}

void dfs(int pos, int group) {
    if (pos == n) {
        double mean = 0.0;
        for (int i = 0; i < m; i++) {
            mean += sum[i];
        }
        mean /= m;
        double variance = calculate_variance(mean);
        if (variance < min_variance) {
            min_variance = variance;
        }
        return;
    }
    for (int i = 0; i < group; i++) {
        sum[i] += a[pos];
        dfs(pos + 1, group);
        sum[i] -= a[pos];
    }
}

double min_variance = INFINITY;

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    quicksort(a, 0, n - 1);
    dfs(0, m);
    printf("%.2f\n", min_variance);
    return 0;
}