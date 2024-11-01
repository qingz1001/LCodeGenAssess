#include <stdio.h>
#include <stdlib.h>

// 交换两个整数的值
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 获取数组中最大值的索引
int getMaxIndex(int arr[], int n) {
    int maxIndex = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] > arr[maxIndex]) {
            maxIndex = i;
        }
    }
    return maxIndex;
}

// 获取数组中最小值的索引
int getMinIndex(int arr[], int n, int start) {
    int minIndex = start;
    for (int i = start + 1; i < n; i++) {
        if (arr[i] < arr[minIndex]) {
            minIndex = i;
        }
    }
    return minIndex;
}

// 对数组进行一次冒泡排序，并返回排序后的结果
void bubbleSort(int arr[], int n, int m) {
    for (int i = 0; i < m; i++) {
        int maxIndex = getMaxIndex(arr, n - i);
        swap(&arr[maxIndex], &arr[n - i - 1]);
    }
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    int fingers[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &fingers[i]);
    }

    bubbleSort(fingers, N, M);

    for (int i = 0; i < N; i++) {
        printf("%d ", fingers[i]);
    }
    printf("\n");

    return 0;
}