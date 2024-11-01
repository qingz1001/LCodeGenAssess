#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 120
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int matrix[MAX_N][MAX_N];
int sum[MAX_N];

int kadane(int* arr, int n) {
    int max_so_far = arr[0];
    int curr_max = arr[0];
    for (int i = 1; i < n; i++) {
        curr_max = MAX(arr[i], curr_max + arr[i]);
        max_so_far = MAX(max_so_far, curr_max);
    }
    return max_so_far;
}

int maxSumRectangle(int n) {
    int maxSum = -127 * MAX_N * MAX_N;
    
    for (int left = 0; left < n; left++) {
        memset(sum, 0, sizeof(sum));
        
        for (int right = left; right < n; right++) {
            for (int i = 0; i < n; i++) {
                sum[i] += matrix[i][right];
            }
            
            int currMaxSum = kadane(sum, n);
            maxSum = MAX(maxSum, currMaxSum);
        }
    }
    
    return maxSum;
}

int main() {
    int n;
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    
    int result = maxSumRectangle(n);
    printf("%d\n", result);
    
    return 0;
}