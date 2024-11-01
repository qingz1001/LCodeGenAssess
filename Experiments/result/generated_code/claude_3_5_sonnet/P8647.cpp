#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

int N, K;
int H[MAX_N], W[MAX_N];

int check(int size) {
    int count = 0;
    for (int i = 0; i < N; i++) {
        count += (H[i] / size) * (W[i] / size);
        if (count >= K) return 1;
    }
    return 0;
}

int binary_search(int left, int right) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (check(mid)) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return right;
}

int main() {
    scanf("%d %d", &N, &K);
    
    int max_side = 0;
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &H[i], &W[i]);
        if (H[i] > max_side) max_side = H[i];
        if (W[i] > max_side) max_side = W[i];
    }

    int result = binary_search(1, max_side);
    printf("%d\n", result);

    return 0;
}