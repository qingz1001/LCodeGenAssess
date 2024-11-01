#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    int min_val;
    for (int i = 0; i < n; i++) {
        if (i < m) {
            min_val = a[0];
            for (int j = 1; j <= i; j++) {
                if (a[j] < min_val) {
                    min_val = a[j];
                }
            }
        } else {
            min_val = a[i - m + 1];
            for (int j = i - m + 2; j <= i; j++) {
                if (a[j] < min_val) {
                    min_val = a[j];
                }
            }
        }
        printf("%d\n", min_val);
    }
    
    return 0;
}