#include <stdio.h>
#include <limits.h>

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    int A[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    long long left = 0, right = 0;
    for (int i = 0; i < N; i++) {
        right += A[i];
        left = left > A[i] ? left : A[i];
    }

    while (left < right) {
        long long mid = (left + right) / 2;
        int segments = 1;
        long long current_sum = 0;

        for (int i = 0; i < N; i++) {
            if (current_sum + A[i] > mid) {
                segments++;
                current_sum = A[i];
            } else {
                current_sum += A[i];
            }
        }

        if (segments <= M) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    printf("%lld\n", left);
    return 0;
}