#include <stdio.h>
#include <limits.h>

#define MAXN 120

int matrix[MAXN][MAXN];

int max(int a, int b) {
    return a > b ? a : b;
}

int kadane(int arr[], int n) {
    int max_ending_here = arr[0];
    int max_so_far = arr[0];
    for (int i = 1; i < n; i++) {
        max_ending_here = max(arr[i], max_ending_here + arr[i]);
        max_so_far = max(max_so_far, max_ending_here);
    }
    return max_so_far;
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    int max_sum = INT_MIN;

    for (int left = 0; left < n; left++) {
        int temp[MAXN] = {0};
        for (int right = left; right < n; right++) {
            for (int i = 0; i < n; i++) {
                temp[i] += matrix[i][right];
            }
            max_sum = max(max_sum, kadane(temp, n));
        }
    }

    printf("%d\n", max_sum);

    return 0;
}