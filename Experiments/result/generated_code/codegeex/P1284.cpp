#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n;
    scanf("%d", &n);
    int lengths[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &lengths[i]);
    }
    
    qsort(lengths, n, sizeof(int), cmp);
    
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += lengths[i];
    }
    
    if (sum < 3) {
        printf("-1\n");
        return 0;
    }
    
    int max_area = 0;
    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            for (int k = j + 1; k < n; k++) {
                int a = lengths[i];
                int b = lengths[j];
                int c = lengths[k];
                
                if (a + b > c && a + c > b && b + c > a) {
                    int area = (a + b + c) * (a + b - c) * (a - b + c) * (-a + b + c) / 16;
                    if (area > max_area) {
                        max_area = area;
                    }
                }
            }
        }
    }
    
    if (max_area == 0) {
        printf("-1\n");
    } else {
        printf("%d\n", max_area / 100);
    }
    
    return 0;
}