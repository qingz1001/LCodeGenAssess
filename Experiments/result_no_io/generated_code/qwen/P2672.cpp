#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);
    
    int S[N], A[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &S[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    
    long long maxFatigue[N + 1];
    for (int X = 1; X <= N; X++) {
        maxFatigue[X] = 0;
        for (int i = 0; i < X; i++) {
            if (i == 0) {
                maxFatigue[X] += S[0] * 2 + A[0];
            } else {
                maxFatigue[X] += S[i] * 2 - S[i - 1] * 2 + A[i];
            }
        }
        
        for (int j = X; j < N; j++) {
            maxFatigue[X] = (maxFatigue[X] > maxFatigue[X] + S[j] * 2 - S[j - X] * 2 + A[j]) ? maxFatigue[X] : maxFatigue[X] + S[j] * 2 - S[j - X] * 2 + A[j];
        }
        
        printf("%lld\n", maxFatigue[X]);
    }
    
    return 0;
}