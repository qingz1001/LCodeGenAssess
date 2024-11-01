#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 10000

long long power(long long base, int exponent) {
    long long result = 1;
    while (exponent > 0) {
        if (exponent & 1)
            result *= base;
        base *= base;
        exponent >>= 1;
    }
    return result;
}

int main() {
    int N, m1, m2;
    int S[MAX_N];
    scanf("%d", &N);
    scanf("%d %d", &m1, &m2);
    
    long long M = power(m1, m2);
    
    for (int i = 0; i < N; i++) {
        scanf("%d", &S[i]);
    }
    
    int minTime = INT_MAX;
    
    for (int i = 0; i < N; i++) {
        long long cellCount = 1;
        int time = 0;
        
        while (cellCount < M) {
            if (cellCount > LLONG_MAX / S[i]) {
                time = -1;
                break;
            }
            cellCount *= S[i];
            time++;
        }
        
        if (time != -1 && cellCount % M == 0) {
            if (time < minTime) {
                minTime = time;
            }
        }
    }
    
    if (minTime == INT_MAX) {
        printf("-1\n");
    } else {
        printf("%d\n", minTime);
    }
    
    return 0;
}