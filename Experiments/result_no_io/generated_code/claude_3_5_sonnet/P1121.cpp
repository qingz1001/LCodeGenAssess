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
    *start = *end = -1;

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

    int a[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int start1, end1;
    long long max_sum = kadane(a, n, &start1, &end1);

    // Case 1: The maximum sum is the sum of two non-overlapping segments
    long long total = 0;
    for (int i = 0; i < n; i++) {
        total += a[i];
        a[i] = -a[i];
    }
    int start2, end2;
    long long min_sum = -kadane(a, n, &start2, &end2);
    long long case1 = total - min_sum;

    // Case 2: The maximum sum is the sum of one segment (wrapping around the array)
    for (int i = 0; i < n; i++) {
        a[i] = -a[i];
    }
    int temp[MAX_N * 2];
    for (int i = 0; i < n * 2; i++) {
        temp[i] = a[i % n];
    }
    long long case2 = kadane(temp, n * 2, &start2, &end2);

    // The result is the maximum of the two cases
    long long result = max(max_sum, max(case1, case2));

    printf("%lld\n", result);

    return 0;
}