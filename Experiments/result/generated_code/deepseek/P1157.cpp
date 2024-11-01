#include <stdio.h>

void printCombination(int arr[], int n, int r) {
    int data[r];
    combinationUtil(arr, data, 0, n-1, 0, r);
}

void combinationUtil(int arr[], int data[], int start, int end, int index, int r) {
    if (index == r) {
        for (int j = 0; j < r; j++) {
            printf("%3d", data[j]);
        }
        printf("\n");
        return;
    }

    for (int i = start; i <= end && end - i + 1 >= r - index; i++) {
        data[index] = arr[i];
        combinationUtil(arr, data, i + 1, end, index + 1, r);
    }
}

int main() {
    int n, r;
    scanf("%d %d", &n, &r);
    int arr[n];
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }
    printCombination(arr, n, r);
    return 0;
}