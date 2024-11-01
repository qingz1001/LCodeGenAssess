#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    
    int *destinations = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &destinations[i]);
    }
    
    int max_floor = 0;
    for (int i = 0; i < n; i++) {
        if (destinations[i] > max_floor) {
            max_floor = destinations[i];
        }
    }
    
    int total_time = max_floor * 6 + (max_floor * 4) + (n * 5) + n;
    
    printf("%d\n", total_time);
    
    free(destinations);
    return 0;
}