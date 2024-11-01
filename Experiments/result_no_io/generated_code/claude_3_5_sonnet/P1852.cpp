#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 3

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sort(int *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

int abs_diff(int a, int b) {
    return abs(a - b);
}

int main() {
    int start[MAX_N], end[MAX_N];
    
    for (int i = 0; i < MAX_N; i++) {
        scanf("%d", &start[i]);
    }
    
    for (int i = 0; i < MAX_N; i++) {
        scanf("%d", &end[i]);
    }
    
    sort(start, MAX_N);
    sort(end, MAX_N);
    
    int diff1 = abs_diff(start[1] - start[0], end[1] - end[0]);
    int diff2 = abs_diff(start[2] - start[1], end[2] - end[1]);
    
    if (diff1 == 0 && diff2 == 0) {
        printf("YES\n");
        int steps = 0;
        for (int i = 0; i < MAX_N; i++) {
            steps += abs_diff(start[i], end[i]);
        }
        printf("%d\n", steps / 2);
    } else {
        printf("NO\n");
    }
    
    return 0;
}