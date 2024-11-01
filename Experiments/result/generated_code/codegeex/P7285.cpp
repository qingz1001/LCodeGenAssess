#include <stdio.h>

int main() {
    int T;
    scanf("%d", &T);
    
    while (T--) {
        int n, maxLen = 0, currentLen = 0, modifiedCount = 0;
        scanf("%d", &n);
        int arr[n];
        
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }
        
        for (int i = 0; i < n; i++) {
            if (arr[i] == 1) {
                currentLen++;
            } else {
                if (currentLen > maxLen) {
                    maxLen = currentLen;
                }
                currentLen = 0;
            }
        }
        
        if (currentLen > maxLen) {
            maxLen = currentLen;
        }
        
        printf("%d\n", maxLen);
        
        for (int i = 0; i < n; i++) {
            if (arr[i] == 0) {
                modifiedCount++;
                printf("1 ");
            } else {
                printf("0 ");
            }
        }
        
        printf("\n");
    }
    
    return 0;
}