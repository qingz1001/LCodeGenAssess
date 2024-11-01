#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    
    int* a = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    int max = 0, min = 0;
    for (int i = 0; i < n; i++) {
        max += a[i];
        min += (a[i] < 0 ? a[i] : 0);
    }
    
    if (min < 0) {
        printf("Impossible\n");
    } else {
        printf("%d\n", (max + min) / min);
    }
    
    free(a);
    return 0;
}