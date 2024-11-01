#include <stdio.h>
#include <stdlib.h>

#define MAXN 1001
#define MAXM 5001

int n, m;
int tasks[MAXN];

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int i, j, k, x, y, b;
    scanf("%d%d", &n, &m);
    
    for (i = 0; i < m; i++) {
        scanf("%d%d%d", &x, &y, &b);
        if (x > y) {
            int temp = x;
            x = y;
            y = temp;
            b = -b;
        }
        tasks[(x-1)*n + y] = b;
    }
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i != j) {
                for (k = 1; k <= n; k++) {
                    if (tasks[(i*n + k)] != 0 && tasks[(j*n + k)] != 0) {
                        if (tasks[(i*n + k)] - tasks[(j*n + k)] > tasks[(i*n + j)]) {
                            printf("NO SOLUTION\n");
                            return 0;
                        }
                    }
                }
            }
        }
    }
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (tasks[(i*n + j)] != 0) {
                for (k = 1; k <= n; k++) {
                    tasks[(i*n + k)] -= tasks[(i*n + j)];
                }
            }
        }
    }
    
    qsort(tasks, n*n, sizeof(int), compare);
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (tasks[(i*n + j)] != 0) {
                for (k = 1; k <= n; k++) {
                    tasks[(i*n + k)] -= tasks[(i*n + j)];
                }
            }
        }
    }
    
    for (i = 0; i < n; i++) {
        printf("%d\n", tasks[(i*n + (n-1))]);
    }
    
    return 0;
}