#include <stdio.h>
#include <stdlib.h>

void solve(int n, int arr[]) {
    int max_len = 0, current_len = 0, zero_count = 0;
    int best_start = 0, best_end = 0, current_start = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] == 1) {
            current_len++;
            if (current_len > max_len) {
                max_len = current_len;
                best_start = current_start;
                best_end = i;
            }
        } else {
            zero_count++;
            current_len = 0;
            current_start = i + 1;
        }
    }

    int max_diff = max_len - zero_count;

    // Modify the array to maximize the difference
    for (int i = 0; i < n; i++) {
        if (i >= best_start && i <= best_end) {
            arr[i] = 1;
        } else if (arr[i] == 0 && zero_count > 0) {
            arr[i] = 1;
            zero_count--;
        }
    }

    printf("%d\n", max_diff);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        int *arr = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }
        solve(n, arr);
        free(arr);
    }
    return 0;
}