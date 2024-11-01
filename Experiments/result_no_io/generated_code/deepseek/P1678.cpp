#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int findClosest(int *arr, int size, int target) {
    int left = 0, right = size - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return 0;
        if (arr[mid] < target) left = mid + 1;
        else right = mid;
    }
    int closest = abs(arr[left] - target);
    if (left > 0) {
        closest = (closest < abs(arr[left - 1] - target)) ? closest : abs(arr[left - 1] - target);
    }
    if (left < size - 1) {
        closest = (closest < abs(arr[left + 1] - target)) ? closest : abs(arr[left + 1] - target);
    }
    return closest;
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    
    int *schools = (int *)malloc(m * sizeof(int));
    int *students = (int *)malloc(n * sizeof(int));
    
    for (int i = 0; i < m; i++) {
        scanf("%d", &schools[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &students[i]);
    }
    
    qsort(schools, m, sizeof(int), compare);
    
    long long dissatisfaction = 0;
    for (int i = 0; i < n; i++) {
        dissatisfaction += findClosest(schools, m, students[i]);
    }
    
    printf("%lld\n", dissatisfaction);
    
    free(schools);
    free(students);
    
    return 0;
}