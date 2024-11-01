#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);
    
    int X, K;
    for (X = 100; X >= 1; X--) {
        for (K = 1; K <= 100; K++) {
            long long total = 0;
            for (int day = 0; day < 7; day++) {
                total += (X + day * K) * 52;
            }
            if (total == N) {
                printf("%d\n%d\n", X, K);
                return 0;
            }
        }
    }
    
    return 0;
}