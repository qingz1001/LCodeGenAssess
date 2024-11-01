#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    
    int *destinations = (int *)malloc(n * sizeof(int));
    if (destinations == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &destinations[i]);
    }
    
    int max_floor = 0;
    for (int i = 0; i < n; i++) {
        if (destinations[i] > max_floor) {
            max_floor = destinations[i];
        }
    }
    
    int total_time = 0;
    
    // Time to go up to the highest floor
    total_time += max_floor * 6;
    
    // Time to go down to the ground floor
    total_time += max_floor * 4;
    
    // Time for opening the door for each person
    total_time += n * 5;
    
    // Time for each person to get off
    total_time += n;
    
    printf("%d\n", total_time);
    
    free(destinations);
    return 0;
}