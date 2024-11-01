#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);
    
    for (int i = 0; i < N; ++i) {
        long long A;
        scanf("%lld", &A);
        
        // Find the position in the sequence
        while (A > 3 * (A / 4)) {
            A = A - A / 2;
        }
        
        // Determine the digit at the given position
        if (A == 1) {
            printf("1\n");
        } else {
            printf("0\n");
        }
    }
    
    return 0;
}