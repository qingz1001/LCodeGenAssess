#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000000000
#define MAX_M 300000

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    long long balls[MAX_M];
    for (int i = 0; i < M; ++i) {
        scanf("%lld", &balls[i]);
    }

    long long left = 0, right = MAX_N, result = MAX_N;

    while (left <= right) {
        long long mid = left + (right - left) / 2;
        long long children = 0;

        for (int i = 0; i < M && children < N; ++i) {
            children += (balls[i] + mid - 1) / mid;
        }

        if (children >= N) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    printf("%lld\n", result);
    return 0;
}