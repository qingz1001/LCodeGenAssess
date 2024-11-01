#include <stdio.h>
#include <limits.h>

int main() {
    int n, T;
    scanf("%d %d", &n, &T);
    
    int max_height = INT_MIN;
    int min_index = -1;
    
    for (int i = 0; i < n; i++) {
        int v, t;
        scanf("%d %d", &v, &t);
        
        int height = v * (T - t);
        if (height > max_height || (height == max_height && i < min_index)) {
            max_height = height;
            min_index = i + 1;
        }
    }
    
    printf("%d\n", min_index);
    
    return 0;
}