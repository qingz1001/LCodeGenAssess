#include <stdio.h>

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    long long total_marbles = 0;
    for (int i = 0; i < M; i++) {
        long long x;
        scanf("%lld", &x);
        total_marbles += x;
    }

    if (total_marbles <= N) {
        printf("1\n");
        return 0;
    }

    long long left = 1, right = total_marbles / N + 1;
    while (left < right) {
        long long mid = (left + right) / 2;
        long long children = 0;

        for (int i = 0; i < M; i++) {
            long long x;
            scanf("%lld", &x);
            children += (x + mid - 1) / mid;
        }

        if (children > N) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    printf("%lld\n", left);
    return 0;
}