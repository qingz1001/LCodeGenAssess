#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    for (int i = 0; i < m; i++) {
        int q;
        scanf("%d", &q);
        
        int left = 0, right = n - 1, mid;
        while (left <= right) {
            mid = (left + right) / 2;
            if (a[mid] == q) {
                while (mid > 0 && a[mid - 1] == q) mid--;
                printf("%d ", mid + 1);
                break;
            } else if (a[mid] < q) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        if (left > right) {
            printf("-1 ");
        }
    }
    
    return 0;
}