#include <stdio.h>
#include <stdlib.h>

#define MAX_N 50000

int stones[MAX_N + 1];
int n, m;

int can_jump(int max_distance) {
    int count = 0;
    for (int i = 1; i <= n; ++i) {
        if (stones[i] - stones[i - 1] > max_distance) {
            ++count;
        }
    }
    return count <= m;
}

int main() {
    int l, n, m;
    scanf("%d %d %d", &l, &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &stones[i]);
    }

    int left = 0, right = l, result = 0;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (can_jump(mid)) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    printf("%d\n", result);
    return 0;
}