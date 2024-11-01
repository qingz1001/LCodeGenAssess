#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 200000

long long max(long long a, long long b) {
    return a > b ? a : b;
}

long long kadane(int arr[], int n, int *start, int *end) {
    long long max_so_far = INT_MIN, max_ending_here = 0;
    int s = 0;
    *start = *end = 0;

    for (int i = 0; i < n; i++) {
        max_ending_here += arr[i];
        if (max_so_far < max_ending_here) {
            max_so_far = max_ending_here;
            *start = s;
            *end = i;
        }
        if (max_ending_here < 0) {
            max_ending_here = 0;
            s = i + 1;
        }
    }
    return max_so_far;
}

int main() {
    int n;
    scanf("%d", &n);

    int arr[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int start1, end1, start2, end2;
    long long max_sum1 = kadane(arr, n, &start1, &end1);

    for (int i = 0; i < n; i++) {
        arr[i] = -arr[i];
    }

    long long min_sum = kadane(arr, n, &start2, &end2);
    long long total_sum = 0;
    for (int i = 0; i < n; i++) {
        arr[i] = -arr[i];
        total_sum += arr[i];
    }

    long long max_sum2 = total_sum + min_sum;

    long long result = max(max_sum1, max_sum2);
    printf("%lld\n", result);

    return 0;
}