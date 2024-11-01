#include <stdio.h>
#include <stdbool.h>

#define MAXN 100000

int N, M;
int A[MAXN];

bool can_split(long long max_sum) {
    long long current_sum = 0;
    int segments = 1;
    for (int i = 0; i < N; i++) {
        if (current_sum + A[i] > max_sum) {
            segments++;
            current_sum = A[i];
            if (segments > M) return false;
        } else {
            current_sum += A[i];
        }
    }
    return true;
}

long long binary_search(long long left, long long right) {
    while (left < right) {
        long long mid = left + (right - left) / 2;
        if (can_split(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

int main() {
    scanf("%d %d", &N, &M);
    long long total_sum = 0;
    long long max_element = 0;
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        total_sum += A[i];
        if (A[i] > max_element) {
            max_element = A[i];
        }
    }

    long long result = binary_search(max_element, total_sum);
    printf("%lld\n", result);

    return 0;
}