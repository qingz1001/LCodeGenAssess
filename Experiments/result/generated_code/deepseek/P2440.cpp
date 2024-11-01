#include <stdio.h>

int n, k;
int logs[100005];

int canCut(int length) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        count += logs[i] / length;
        if (count >= k) return 1;
    }
    return 0;
}

int main() {
    scanf("%d %d", &n, &k);
    int max_length = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &logs[i]);
        if (logs[i] > max_length) max_length = logs[i];
    }

    int left = 1, right = max_length;
    int result = 0;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (canCut(mid)) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    printf("%d\n", result);
    return 0;
}