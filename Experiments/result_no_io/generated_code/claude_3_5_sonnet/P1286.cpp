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

int solve(int index, int sum) {
    if (index == n) {
        return 1;
    }
    
    for (int i = 0; i <= sums[0]; i++) {
        if (!used[i] && (index == 0 || i > numbers[index-1])) {
            int valid = 1;
            for (int j = 0; j < index && valid; j++) {
                if (!used[i + numbers[j]]) {
                    valid = 0;
                }
            }
            
            if (valid) {
                numbers[index] = i;
                used[i] = 1;
                for (int j = 0; j < index; j++) {
                    used[i + numbers[j]]--;
                }
                
                if (solve(index + 1, sum + i)) {
                    return 1;
                }
                
                used[i] = 0;
                for (int j = 0; j < index; j++) {
                    used[i + numbers[j]]++;
                }
            }
        }
    }
    
    return 0;
}

int main() {
    while (scanf("%d", &n) != EOF) {
        int count = n * (n - 1) / 2;
        for (int i = 0; i < count; i++) {
            scanf("%d", &sums[i]);
        }
        
        qsort(sums, count, sizeof(int), compare);
        memset(used, 0, sizeof(used));
        for (int i = 0; i < count; i++) {
            used[sums[i]]++;
        }
        
        if (solve(0, 0)) {
            for (int i = 0; i < n; i++) {
                printf("%d", numbers[i]);
                if (i < n - 1) {
                    printf(" ");
                }
            }
            printf("\n");
        } else {
            printf("Impossible\n");
        }
    }
    
    return 0;
}