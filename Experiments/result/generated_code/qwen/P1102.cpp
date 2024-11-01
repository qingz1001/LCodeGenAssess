#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, C;
    scanf("%d %d", &N, &C);
    
    int *numbers = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &numbers[i]);
    }
    
    long long count = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (numbers[i] - numbers[j] == C) {
                count++;
            }
        }
    }
    
    printf("%lld\n", count);
    
    free(numbers);
    return 0;
}