#include <stdio.h>

void combination(int n, int r, int *arr, int index, int start) {
    if (index == r) {
        for (int i = 0; i < r; i++) {
            printf("%3d", arr[i]);
        }
        printf("\n");
        return;
    }
    for (int i = start; i <= n; i++) {
        arr[index] = i;
        combination(n, r, arr, index + 1, i + 1);
    }
}

int main() {
    int n, r;
    scanf("%d %d", &n, &r);
    int arr[21];
    combination(n, r, arr, 0, 1);
    return 0;
}