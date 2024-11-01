#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

int main() {
    int N, C;
    scanf("%d%d", &N, &C);
    int *arr = (int*)malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }
    qsort(arr, N, sizeof(int), cmp);
    int l = 1, r = arr[N-1] - arr[0], ans = 0;
    while (l <= r) {
        int mid = (l + r) / 2;
        int cnt = 1, pos = arr[0];
        for (int i = 1; i < N; i++) {
            if (arr[i] - pos >= mid) {
                cnt++;
                pos = arr[i];
            }
        }
        if (cnt >= C) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    printf("%d\n", ans);
    free(arr);
    return 0;
}