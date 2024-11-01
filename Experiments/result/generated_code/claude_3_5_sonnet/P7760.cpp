#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, X;
    scanf("%d", &N);
    scanf("%d", &X);
    
    long long total = 0;
    
    for(int i = 0; i < N; i++) {
        int P1, P2, P3 = -1;
        scanf("%d %d", &P1, &P2);
        
        char c = getchar();
        if(c == '\n') {
            if(abs(P1 - P2) <= X) {
                total += (P1 > P2) ? P1 : P2;
            } else {
                total += (P1 < P2) ? P1 : P2;
            }
        } else {
            scanf("%d", &P3);
            if(abs(P1 - P2) <= X) {
                total += (P1 > P2) ? P1 : P2;
            } else {
                total += P3;
            }
        }
    }
    
    printf("%lld\n", total);
    
    return 0;
}