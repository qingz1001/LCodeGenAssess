#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int count1 = 0, count2 = 0, count3 = 0;
    int arr[1000];

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        if (arr[i] == 1) count1++;
        else if (arr[i] == 2) count2++;
        else count3++;
    }

    int swaps = 0;
    int i = 0, j = count1, k = count1 + count2;

    // Phase 1: Fix 1s in the first segment
    for (int p = 0; p < count1; p++) {
        if (arr[p] == 2) {
            while (j < n && arr[j] != 1) j++;
            if (j < n) {
                int temp = arr[p];
                arr[p] = arr[j];
                arr[j] = temp;
                swaps++;
            }
        } else if (arr[p] == 3) {
            while (k < n && arr[k] != 1) k++;
            if (k < n) {
                int temp = arr[p];
                arr[p] = arr[k];
                arr[k] = temp;
                swaps++;
            }
        }
    }

    // Phase 2: Fix 2s in the second segment
    for (int p = count1; p < count1 + count2; p++) {
        if (arr[p] == 3) {
            while (k < n && arr[k] != 2) k++;
            if (k < n) {
                int temp = arr[p];
                arr[p] = arr[k];
                arr[k] = temp;
                swaps++;
            }
        }
    }

    printf("%d\n", swaps);
    return 0;
}