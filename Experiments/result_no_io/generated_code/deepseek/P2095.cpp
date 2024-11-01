#include <stdio.h>
#include <stdlib.h>

#define MAX_N 200
#define MAX_M 100
#define MAX_K 100

typedef struct {
    int fat;
    int category;
} Food;

int compare(const void *a, const void *b) {
    return ((Food *)b)->fat - ((Food *)a)->fat;
}

int main() {
    int n, m, k;
    int max_per_category[MAX_K];
    Food foods[MAX_N];

    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i < k; i++) {
        scanf("%d", &max_per_category[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &foods[i].fat, &foods[i].category);
        foods[i].category--; // Convert to 0-based index
    }

    // Sort foods by fat in descending order
    qsort(foods, n, sizeof(Food), compare);

    int total_fat = 0;
    int eaten_per_category[MAX_K] = {0};

    for (int i = 0; i < n && m > 0; i++) {
        int category = foods[i].category;
        if (eaten_per_category[category] < max_per_category[category]) {
            total_fat += foods[i].fat;
            eaten_per_category[category]++;
            m--;
        }
    }

    printf("%d\n", total_fat);
    return 0;
}