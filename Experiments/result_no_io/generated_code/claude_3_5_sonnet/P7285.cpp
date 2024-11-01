#include <stdio.h>
#include <string.h>

#define MAX_N 100005

int arr[MAX_N], result[MAX_N];
int n;

int solve() {
    int max_len = 0, curr_len = 0, zeros = 0;
    int left = 0, right = 0, best_left = 0, best_right = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] == 1) {
            curr_len++;
        } else {
            zeros++;
            if (curr_len > max_len) {
                max_len = curr_len;
                best_left = left;
                best_right = i - 1;
            }
            left = i + 1;
            curr_len = 0;
        }
    }

    if (curr_len > max_len) {
        max_len = curr_len;
        best_left = left;
        best_right = n - 1;
    }

    int extend_left = best_left, extend_right = best_right;
    while (extend_left > 0 && arr[extend_left - 1] == 0) extend_left--;
    while (extend_right < n - 1 && arr[extend_right + 1] == 0) extend_right++;

    int modified = extend_right - extend_left + 1 - max_len;
    int new_max_len = extend_right - extend_left + 1;

    memcpy(result, arr, sizeof(int) * n);
    for (int i = extend_left; i <= extend_right; i++) {
        result[i] = 1;
    }

    return new_max_len - modified;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }

        int max_diff = solve();

        printf("%d\n", max_diff);
        for (int i = 0; i < n; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
    }

    return 0;
}