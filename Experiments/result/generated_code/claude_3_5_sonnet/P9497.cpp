#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1003
#define MAX_Q 500005

int n, q;
int a[MAX_N][MAX_N];
int max_in_col[MAX_N];

int compare(const void *a, const void *b) {
    return *(int*)b - *(int*)a;
}

int main() {
    scanf("%d %d", &n, &q);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    
    for (int j = 0; j < n; j++) {
        max_in_col[j] = a[0][j];
        for (int i = 1; i < n; i++) {
            if (a[i][j] > max_in_col[j]) {
                max_in_col[j] = a[i][j];
            }
        }
    }
    
    qsort(max_in_col, n, sizeof(int), compare);
    
    int v;
    for (int i = 0; i < q; i++) {
        scanf("%d", &v);
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (max_in_col[j] >= v) {
                count++;
            } else {
                break;
            }
        }
        printf("%d\n", count);
    }
    
    return 0;
}