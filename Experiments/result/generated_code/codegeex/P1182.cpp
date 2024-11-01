#include <stdio.h>
#include <limits.h>

#define MAXN 100005

int A[MAXN];

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    int sum = 0, max = 0;
    for (int i = 0; i < N; i++) {
        sum += A[i];
        max = (max > A[i]) ? max : A[i];
    }

    int left = max, right = sum;
    while (left < right) {
        int mid = (left + right) / 2;
        int count = 1, temp_sum = 0;
        for (int i = 0; i < N; i++) {
            if (temp_sum + A[i] > mid) {
                count++;
                temp_sum = A[i];
            } else {
                temp_sum += A[i];
            }
        }
        if (count > M) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    printf("%d\n", left);
    return 0;
}