#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100001

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    int *tech = (int *)malloc(n * sizeof(int));
    int *special = (int *)malloc(m * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &tech[i]);
    }
    
    for (int i = 0; i < m; i++) {
        scanf("%d", &special[i]);
    }
    
    int result[MAX_N] = {0};
    int count = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (tech[i] == special[j]) {
                result[count++] = tech[i];
                break;
            }
        }
    }
    
    printf("%d", result[0]);
    for (int i = 1; i < count; i++) {
        printf(" %d", result[i]);
    }
    printf("\n");
    
    free(tech);
    free(special);
    
    return 0;
}