#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    int *a = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    int *q = (int *)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++) {
        scanf("%d", &q[i]);
    }
    
    for (int i = 0; i < m; i++) {
        int left = 0, right = n - 1, mid;
        int found = 0;
        while (left <= right) {
            mid = (left + right) / 2;
            if (a[mid] == q[i]) {
                found = 1;
                while (mid > 0 && a[mid - 1] == q[i]) mid--;
                printf("%d ", mid + 1);
                break;
            } else if (a[mid] < q[i]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        if (!found) printf("-1 ");
    }
    
    free(a);
    free(q);
    return 0;
}