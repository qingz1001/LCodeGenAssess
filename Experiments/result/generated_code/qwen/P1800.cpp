#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    int *d1 = (int *)malloc(n * sizeof(int));
    int *d2 = (int *)malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &d1[i], &d2[i]);
    }
    
    int max_time = 0;
    for (int i = 0; i < n; i++) {
        int time1 = (m + d1[i] - 1) / d1[i];
        int time2 = (m + d2[i] - 1) / d2[i];
        max_time = (time1 > time2) ? time1 : time2;
    }
    
    printf("%d\n", max_time);
    
    free(d1);
    free(d2);
    
    return 0;
}