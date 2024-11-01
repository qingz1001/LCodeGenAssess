#include <stdio.h>

void printCombination(int data[], int start, int end, int index, int r);
void combinationUtil(int arr[], int n, int r);

int main() {
    int n, r;
    scanf("%d %d", &n, &r);
    int arr[n];
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }
    combinationUtil(arr, n, r);
    return 0;
}

void printCombination(int data[], int start, int end, int index, int r) {
    if (index == r) {
        for (int j = 0; j < r; j++) {
            printf("%3d", data[j]);
        }
        printf("\n");
        return;
    }

    for (int i = start; i <= end && end - i + 1 >= r - index; i++) {
        data[index] = i;
        printCombination(data, i + 1, end, index + 1, r);
    }
}

void combinationUtil(int arr[], int n, int r) {
    int data[r];
    printCombination(data, 0, n - 1, 0, r);
}