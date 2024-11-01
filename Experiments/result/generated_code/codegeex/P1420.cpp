#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    int maxLength = 1;
    int currentLength = 1;
    
    for (int i = 1; i < n; i++) {
        if (a[i] == a[i - 1] + 1) {
            currentLength++;
        } else {
            if (currentLength > maxLength) {
                maxLength = currentLength;
            }
            currentLength = 1;
        }
    }
    
    if (currentLength > maxLength) {
        maxLength = currentLength;
    }
    
    printf("%d\n", maxLength);
    
    return 0;
}