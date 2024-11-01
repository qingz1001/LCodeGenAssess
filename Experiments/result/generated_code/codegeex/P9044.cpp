#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    
    int *a = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    // Sort the array in descending order
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] < a[j + 1]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
    
    int giftCount = 0;
    int i = 0;
    while (i < n && giftCount < k) {
        if (i == 0 || a[i] != a[i - 1]) {
            giftCount++;
        }
        i++;
    }
    
    printf("%d\n", giftCount);
    
    free(a);
    return 0;
}