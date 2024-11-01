#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int t, n;
    scanf("%d %d", &t, &n);
    
    int x[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &x[i]);
    }
    
    qsort(x, n, sizeof(int), compare);
    
    int count = 0;
    int left = 0, right = n - 1;
    
    while (left <= right) {
        if (abs(x[left]) + abs(x[right]) <= t) {
            count += 2;
            left++;
            right--;
        } else if (abs(x[left]) > abs(x[right])) {
            count++;
            left++;
        } else {
            count++;
            right--;
        }
    }
    
    printf("%d\n", count);
    
    return 0;
}