#include <stdio.h>
#include <stdbool.h>

bool canPartition(int arr[], int n) {
    if (n % 2 != 0) return false; // 长度必须为偶数
    int first[n/2 + 1], second[n/2 + 1];
    int firstSize = 0, secondSize = 0;

    first[0] = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > first[firstSize]) {
            first[++firstSize] = arr[i];
        } else if (arr[i] > second[secondSize]) {
            second[++secondSize] = arr[i];
        } else {
            return false;
        }
    }

    if (firstSize == n / 2 && secondSize == n / 2) return true;
    return false;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int N;
        scanf("%d", &N);
        int arr[N];
        for (int i = 0; i < N; i++) {
            scanf("%d", &arr[i]);
        }
        if (canPartition(arr, N)) {
            printf("Yes!\n");
        } else {
            printf("No!\n");
        }
    }
    return 0;
}