#include <stdio.h>
#include <stdlib.h>

#define MAXN 100000

int N, K;
int H[MAXN], W[MAXN];

int can_cut(int size) {
    int count = 0;
    for (int i = 0; i < N; i++) {
        count += (H[i] / size) * (W[i] / size);
        if (count >= K) return 1;
    }
    return 0;
}

int main() {
    scanf("%d %d", &N, &K);
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &H[i], &W[i]);
    }

    int left = 1, right = 100000;
    while (left < right) {
        int mid = (left + right + 1) / 2;
        if (can_cut(mid)) {
            left = mid;
        } else {
            right = mid - 1;
        }
    }

    printf("%d\n", left);
    return 0;
}