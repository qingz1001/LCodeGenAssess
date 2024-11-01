#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int swaps = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] != i + 1) {
            int j = i + 1;
            while (j < n && arr[j] != i + 1) {
                j++;
            }
            if (j < n) {
                int temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
                swaps++;
            }
        }
    }

    printf("%d\n", swaps);
    return 0;
}