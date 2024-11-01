#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int index;
} Number;

int compare(const void *a, const void *b) {
    return ((Number *)b)->value - ((Number *)a)->value;
}

int main() {
    Number numbers[8];
    int i, sum = 0;
    
    for (i = 0; i < 8; i++) {
        scanf("%d", &numbers[i].value);
        numbers[i].index = i + 1;
    }
    
    qsort(numbers, 8, sizeof(Number), compare);
    
    for (i = 0; i < 5; i++) {
        sum += numbers[i].value;
    }
    
    printf("%d\n", sum);
    
    int indices[5];
    for (i = 0; i < 5; i++) {
        indices[i] = numbers[i].index;
    }
    
    qsort(indices, 5, sizeof(int), (int (*)(const void*, const void*))strcmp);
    
    for (i = 0; i < 5; i++) {
        printf("%d ", indices[i]);
    }
    
    return 0;
}