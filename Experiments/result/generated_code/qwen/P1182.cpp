#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define INF 0x3f3f3f3f

int A[MAXN];
int N, M;

int check(int mid) {
    int segments = 1;
    int sum = 0;
    for (int i = 0; i < N; ++i) {
        if (sum + A[i] > mid) {
            segments++;
            sum = A[i];
        } else {
            sum += A[i];
        }
    }
    return segments <= M;
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; ++i) {
        scanf("%d", &A[i]);
    }

    int left = 0, right = 0;
    for (int i = 0; i < N; ++i) {
        right += A[i];
        left = left < A[i] ? A[i] : left;
    }

    while (left < right) {
        int mid = (left + right) / 2;
        if (check(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    printf("%d\n", left);
    return 0;
}