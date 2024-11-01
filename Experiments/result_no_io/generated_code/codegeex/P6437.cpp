#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int a[100];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    int maxSum = 0;
    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            for (int k = j + 1; k < n; k++) {
                int sum = a[i] + a[j] + a[k];
                if (sum <= m) {
                    maxSum = (sum > maxSum) ? sum : maxSum;
                }
            }
        }
    }
    
    printf("%d\n", maxSum);
    return 0;
}