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
        else if (arr[i] == 3) count3++;
    }

    int misplaced1 = 0, misplaced2 = 0, misplaced3 = 0;

    for (int i = 0; i < count1; i++) {
        if (arr[i] != 1) misplaced1++;
    }
    for (int i = count1; i < count1 + count2; i++) {
        if (arr[i] != 2) misplaced2++;
    }
    for (int i = count1 + count2; i < n; i++) {
        if (arr[i] != 3) misplaced3++;
    }

    int swaps = 0;
    int min_misplaced = misplaced1 < misplaced2 ? misplaced1 : misplaced2;
    min_misplaced = min_misplaced < misplaced3 ? min_misplaced : misplaced3;

    swaps += min_misplaced;
    misplaced1 -= min_misplaced;
    misplaced2 -= min_misplaced;
    misplaced3 -= min_misplaced;

    swaps += (misplaced1 + misplaced2 + misplaced3);

    printf("%d\n", swaps);

    return 0;
}