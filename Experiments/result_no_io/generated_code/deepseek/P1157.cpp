#include <stdio.h>

void printCombination(int arr[], int data[], int start, int end, int index, int r) {
    if (index == r) {
        for (int i = 0; i < r; i++) {
            printf("%3d", data[i]);
        }
        printf("\n");
        return;
    }

    for (int i = start; i <= end && end - i + 1 >= r - index; i++) {
        data[index] = arr[i];
        printCombination(arr, data, i + 1, end, index + 1, r);
    }
}

void generateCombinations(int n, int r) {
    int arr[n];
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    int data[r];
    printCombination(arr, data, 0, n - 1, 0, r);
}

int main() {
    int n, r;
    scanf("%d %d", &n, &r);
    generateCombinations(n, r);
    return 0;
}