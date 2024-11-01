#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, beginLevel, maxLevel;
    scanf("%d %d %d", &n, &beginLevel, &maxLevel);
    
    int *changes = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &changes[i]);
    }
    
    int currentVolume = beginLevel;
    for (int i = 0; i < n; i++) {
        if (currentVolume + changes[i] > maxLevel) {
            printf("-1\n");
            free(changes);
            return 0;
        } else if (currentVolume + changes[i] < 0) {
            printf("-1\n");
            free(changes);
            return 0;
        } else {
            currentVolume += changes[i];
        }
    }
    
    printf("%d\n", currentVolume);
    free(changes);
    return 0;
}