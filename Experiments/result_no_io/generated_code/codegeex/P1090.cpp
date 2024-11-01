#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    
    int *weights = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &weights[i]);
    }
    
    // 使用最小堆来存储果子的重量
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(weights, n, i);
    }
    
    long long total_cost = 0;
    while (n > 1) {
        int min1 = extract_min(weights, n--);
        int min2 = extract_min(weights, n--);
        int new_weight = min1 + min2;
        total_cost += new_weight;
        insert(weights, n++, new_weight);
    }
    
    printf("%lld\n", total_cost);
    free(weights);
    return 0;
}

void heapify(int *arr, int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && arr[left] < arr[smallest]) {
        smallest = left;
    }
    
    if (right < n && arr[right] < arr[smallest]) {
        smallest = right;
    }
    
    if (smallest != i) {
        int temp = arr[i];
        arr[i] = arr[smallest];
        arr[smallest] = temp;
        
        heapify(arr, n, smallest);
    }
}

int extract_min(int *arr, int n) {
    int min = arr[0];
    arr[0] = arr[n - 1];
    heapify(arr, n - 1, 0);
    return min;
}

void insert(int *arr, int n, int key) {
    arr[n - 1] = key;
    int i = n - 1;
    
    while (i > 0 && arr[(i - 1) / 2] > arr[i]) {
        int temp = arr[i];
        arr[i] = arr[(i - 1) / 2];
        arr[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}