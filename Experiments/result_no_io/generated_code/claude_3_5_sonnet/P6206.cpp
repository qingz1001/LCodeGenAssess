#include <stdio.h>

long long cowGame(long long N) {
    long long score = 0;
    
    while (N != 1) {
        if (N % 2 == 1) {
            N = N * 3 + 1;
        } else {
            N = N / 2;
        }
        score++;
    }
    
    return score;
}

int main() {
    long long N;
    scanf("%lld", &N);
    
    long long result = cowGame(N);
    printf("%lld\n", result);
    
    return 0;
}