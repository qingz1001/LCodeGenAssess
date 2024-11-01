#include <stdio.h>
#include <limits.h>

int main() {
    int n, T;
    scanf("%d %d", &n, &T);
    
    int v[n], t[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &v[i], &t[i]);
    }
    
    int min_index = -1;
    int max_height = INT_MIN;
    
    for (int i = 0; i < n; i++) {
        int height = v[i] * (T - t[i]);
        if (height > max_height || (height == max_height && (min_index == -1 || i < min_index))) {
            max_height = height;
            min_index = i;
        }
    }
    
    printf("%d\n", min_index + 1);
    
    return 0;
}