#include <stdio.h>

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    int heights[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &heights[i]);
    }

    int low = 0, high = 400000; // 树的高度最大为400000
    while (low < high) {
        int mid = (low + high + 1) / 2;
        long long total = 0;
        for (int i = 0; i < N; i++) {
            if (heights[i] > mid) {
                total += heights[i] - mid;
            }
        }
        if (total >= M) {
            low = mid;
        } else {
            high = mid - 1;
        }
    }

    printf("%d\n", low);
    return 0;
}