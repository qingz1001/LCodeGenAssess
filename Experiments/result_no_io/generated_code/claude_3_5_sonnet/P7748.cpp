#include <stdio.h>

int main() {
    int K, N;
    scanf("%d", &K);
    scanf("%d", &N);
    
    int currentPlayer = K;
    int totalTime = 0;
    
    for (int i = 0; i < N; i++) {
        int T;
        char result;
        scanf("%d %c", &T, &result);
        
        totalTime += T;
        
        if (totalTime >= 210) {
            printf("%d\n", currentPlayer);
            return 0;
        }
        
        if (result == 'T') {
            currentPlayer = (currentPlayer % 8) + 1;
        }
    }
    
    printf("%d\n", currentPlayer);
    return 0;
}