#include <stdio.h>
#include <stdlib.h>

#define MAX_M 300000

long long marbles[MAX_M];
int N, M;

int check(long long max_marbles) {
    long long children = 0;
    for (int i = 0; i < M; i++) {
        children += marbles[i] / max_marbles;
    }
    return children >= N;
}

long long binary_search() {
    long long left = 1, right = 1000000000;
    while (left < right) {
        long long mid = left + (right - left + 1) / 2;
        if (check(mid)) {
            left = mid;
        } else {
            right = mid - 1;
        }
    }
    return left;
}

int main() {
    scanf("%d %d", &N, &M);
    
    for (int i = 0; i < M; i++) {
        scanf("%lld", &marbles[i]);
    }
    
    printf("%lld\n", binary_search());
    
    return 0;
}