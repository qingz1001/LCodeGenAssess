#include <stdio.h>

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

int binary_search() {
    int left = 1, right = 100000;
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
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &H[i], &W[i]);
    }
    
    int result = binary_search();
    printf("%d\n", result);
    
    return 0;
}