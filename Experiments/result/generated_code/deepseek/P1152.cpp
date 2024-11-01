#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    bool diffs[n];
    for (int i = 0; i < n; i++) {
        diffs[i] = false;
    }

    for (int i = 1; i < n; i++) {
        int diff = abs(arr[i] - arr[i - 1]);
        if (diff >= 1 && diff <= n - 1) {
            diffs[diff] = true;
        }
    }

    bool jolly = true;
    for (int i = 1; i < n; i++) {
        if (!diffs[i]) {
            jolly = false;
            break;
        }
    }

    if (jolly) {
        printf("Jolly\n");
    } else {
        printf("Not jolly\n");
    }

    return 0;
}