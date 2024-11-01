#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int fat; // 脂肪指数
    int category; // 类别
} Food;

int compare(const void *a, const void *b) {
    Food *foodA = (Food *)a;
    Food *foodB = (Food *)b;
    if (foodA->fat < foodB->fat) return 1;
    if (foodA->fat > foodB->fat) return -1;
    return 0;
}

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    
    int max_foods[k];
    for (int i = 0; i < k; i++) {
        scanf("%d", &max_foods[i]);
    }
    
    Food foods[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &foods[i].fat, &foods[i].category);
    }
    
    qsort(foods, n, sizeof(Food), compare);
    
    int total_fat = 0;
    int eaten = 0;
    
    for (int i = 0; i < n && eaten < m; i++) {
        if (foods[i].category <= k && eaten < max_foods[foods[i].category - 1]) {
            total_fat += foods[i].fat;
            eaten++;
        }
    }
    
    printf("%d\n", total_fat);
    
    return 0;
}