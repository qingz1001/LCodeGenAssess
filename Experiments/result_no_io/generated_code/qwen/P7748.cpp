#include <stdio.h>

int main() {
    int K, N;
    scanf("%d %d", &K, &N);
    
    for (int i = 0; i < N; i++) {
        int T;
        char C;
        scanf("%d %c", &T, &C);
        
        if (C == 'T') {
            K = (K - 1 + 7) % 8 + 1;
        }
    }
    
    printf("%d\n", K);
    
    return 0;
}