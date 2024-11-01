#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    int a[n], b[n];
    
    for (int i = 0; i < n; i++) {
        scanf("%1d", &a[i]);
    }
    
    for (int i = 0; i < n; i++) {
        scanf("%1d", &b[i]);
    }
    
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            count++;
        }
    }
    
    printf("%d\n", count / 2);
    
    return 0;
}