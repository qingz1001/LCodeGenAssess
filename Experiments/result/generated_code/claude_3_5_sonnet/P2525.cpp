#include <stdio.h>
#include <stdbool.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

bool prevPermutation(int arr[], int n) {
    int i = n - 2;
    while (i >= 0 && arr[i] <= arr[i + 1]) {
        i--;
    }
    
    if (i < 0) {
        return false;
    }
    
    int j = n - 1;
    while (j > i && arr[j] >= arr[i]) {
        j--;
    }
    
    swap(&arr[i], &arr[j]);
    
    int left = i + 1, right = n - 1;
    while (left < right) {
        swap(&arr[left], &arr[right]);
        left++;
        right--;
    }
    
    return true;
}

int main() {
    int N;
    scanf("%d", &N);
    
    int arr[9];
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }
    
    if (prevPermutation(arr, N)) {
        for (int i = 0; i < N; i++) {
            printf("%d ", arr[i]);
        }
    } else {
        printf("ERROR");
    }
    
    return 0;
}