#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, C;
    scanf("%d %d", &N, &C);
    
    int *arr = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }
    
    int count = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (arr[i] - arr[j] == C) {
                count++;
            }
        }
    }
    
    printf("%d\n", count);
    
    free(arr);
    return 0;
}