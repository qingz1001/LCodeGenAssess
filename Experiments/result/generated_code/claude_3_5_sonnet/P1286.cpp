#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 10
#define MAX_SUM 100000

int n, sums[MAX_N * (MAX_N - 1) / 2];
int numbers[MAX_N];
int used[MAX_SUM + 1];

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int solve(int index) {
    if (index == n) {
        return 1;
    }
    
    if (index == n - 1) {
        int last = sums[0] - numbers[0];
        for (int i = 1; i < n - 1; i++) {
            if (last != sums[i] - numbers[i]) {
                return 0;
            }
        }
        numbers[index] = last;
        return 1;
    }
    
    for (int i = 0; i <= MAX_SUM; i++) {
        if (used[i]) continue;
        
        int valid = 1;
        for (int j = 0; j < index; j++) {
            int sum = i + numbers[j];
            if (sum > MAX_SUM || !used[sum]) {
                valid = 0;
                break;
            }
        }
        
        if (valid) {
            numbers[index] = i;
            used[i] = 1;
            for (int j = 0; j < index; j++) {
                used[i + numbers[j]]--;
            }
            
            if (solve(index + 1)) {
                return 1;
            }
            
            used[i] = 0;
            for (int j = 0; j < index; j++) {
                used[i + numbers[j]]++;
            }
        }
    }
    
    return 0;
}

int main() {
    while (scanf("%d", &n) != EOF) {
        memset(used, 0, sizeof(used));
        
        for (int i = 0; i < n * (n - 1) / 2; i++) {
            scanf("%d", &sums[i]);
            used[sums[i]]++;
        }
        
        qsort(sums, n * (n - 1) / 2, sizeof(int), compare);
        
        if (solve(0)) {
            for (int i = 0; i < n; i++) {
                printf("%d", numbers[i]);
                if (i < n - 1) printf(" ");
            }
            printf("\n");
        } else {
            printf("Impossible\n");
        }
    }
    
    return 0;
}