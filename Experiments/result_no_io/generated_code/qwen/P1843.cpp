#include <stdio.h>
#include <stdlib.h>

#define MAX_N 500005

int main() {
    int n, a, b;
    scanf("%d %d %d", &n, &a, &b);
    
    int w[MAX_N];
    for (int i = 0; i < n; ++i) {
        scanf("%d", &w[i]);
    }
    
    // Sort the array to process clothes with lower humidity first
    qsort(w, n, sizeof(int), (int (*)(const void *, const void *))strcmp);
    
    int time = 0;
    for (int i = 0; i < n; ++i) {
        if (w[i] > 0) {
            time++;
            w[i] -= a + b;
            for (int j = i - 1; j >= 0 && w[j] > 0; --j) {
                if (w[j] <= a + b) {
                    w[j] = 0;
                    break;
                } else {
                    w[j] -= a + b;
                }
            }
        }
    }
    
    printf("%d\n", time);
    
    return 0;
}