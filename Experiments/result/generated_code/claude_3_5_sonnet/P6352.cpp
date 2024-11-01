#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int numbers[3];
    scanf("%d %d %d", &numbers[0], &numbers[1], &numbers[2]);
    
    qsort(numbers, 3, sizeof(int), compare);
    
    int diff1 = numbers[1] - numbers[0];
    int diff2 = numbers[2] - numbers[1];
    
    if (diff1 == diff2) {
        printf("%d\n", numbers[2] + diff1);
    } else if (diff1 > diff2) {
        printf("%d\n", numbers[0] + diff2);
    } else {
        printf("%d\n", numbers[1] + diff1);
    }
    
    return 0;
}