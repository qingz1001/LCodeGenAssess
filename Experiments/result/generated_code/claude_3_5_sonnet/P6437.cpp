#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n, m;
    int numbers[MAX_N];
    
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &numbers[i]);
    }
    
    qsort(numbers, n, sizeof(int), compare);
    
    int max_sum = 0;
    
    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            int k = n - 1;
            while (k > j && numbers[i] + numbers[j] + numbers[k] > m) {
                k--;
            }
            if (k > j) {
                int sum = numbers[i] + numbers[j] + numbers[k];
                if (sum > max_sum) {
                    max_sum = sum;
                }
            }
        }
    }
    
    printf("%d\n", max_sum);
    
    return 0;
}