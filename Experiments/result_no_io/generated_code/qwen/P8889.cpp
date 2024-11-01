#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    int* a = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    int* b = (int*)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++) {
        scanf("%d", &b[i]);
    }
    
    int segments = 0;
    int in_segment = 0;
    
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < m; j++) {
            if (a[i] == b[j]) {
                found = 1;
                break;
            }
        }
        
        if (found) {
            if (!in_segment) {
                segments++;
                in_segment = 1;
            }
        } else {
            in_segment = 0;
        }
    }
    
    printf("%d\n", segments);
    
    free(a);
    free(b);
    
    return 0;
}