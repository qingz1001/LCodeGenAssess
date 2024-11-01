#include <stdio.h>

int main() {
    int K, N;
    scanf("%d %d", &K, &N);
    
    for (int i = 0; i < N; i++) {
        int T;
        char result;
        scanf("%d %c", &T, &result);
        
        if (result == 'T') {
            K = (K + 1) % 8;
            if (K == 0) K = 8;
        }
    }
    
    printf("%d\n", K);
    
    return 0;
}