#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    for (int i = 0; i < n; i++) {
        int min = a[i];
        int start = i - m < 0 ? 0 : i - m;
        for (int j = start; j < i; j++) {
            if (a[j] < min) {
                min = a[j];
            }
        }
        printf("%d\n", min);
    }
    
    return 0;
}