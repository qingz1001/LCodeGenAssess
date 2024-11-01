#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 10000

long long power(long long base, int exp) {
    long long result = 1;
    while (exp) {
        if (exp & 1) result *= base;
        base *= base;
        exp >>= 1;
    }
    return result;
}

int main() {
    int N, m1, m2;
    long long M, S[MAX_N];
    
    scanf("%d", &N);
    scanf("%d %d", &m1, &m2);
    M = power(m1, m2);
    
    for (int i = 0; i < N; i++) {
        scanf("%lld", &S[i]);
    }
    
    long long min_time = -1;
    for (int i = 0; i < N; i++) {
        long long cells = 1;
        int time = 0;
        while (cells < M) {
            cells *= S[i];
            time++;
            if (cells > M && cells % M != 0) {
                cells = M + 1;  // Make it impossible to divide evenly
                break;
            }
        }
        if (cells % M == 0) {
            if (min_time == -1 || time < min_time) {
                min_time = time;
            }
        }
    }
    
    printf("%lld\n", min_time);
    
    return 0;
}