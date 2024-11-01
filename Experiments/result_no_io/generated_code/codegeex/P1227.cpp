#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
    if (n % 2 != 0) {
        printf("This is a dangerous situation!\n");
        return 0;
    }
    
    int x[20001], y[20001];
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &x[i], &y[i]);
    }
    
    int mid = n / 2;
    for (int i = 1; i <= mid; i++) {
        if (x[i] != x[n - i + 1] || y[i] != y[n - i + 1]) {
            printf("This is a dangerous situation!\n");
            return 0;
        }
    }
    
    printf("V.I.P. should stay at (%.1f,%.1f).\n", (float)(x[mid] + x[mid + 1]) / 2, (float)(y[mid] + y[mid + 1]) / 2);
    
    return 0;
}