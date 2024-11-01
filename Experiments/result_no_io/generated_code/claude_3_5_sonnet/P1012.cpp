#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 20
#define MAX_LEN 10

int compare(const void *a, const void *b) {
    char ab[MAX_LEN * 2 + 1], ba[MAX_LEN * 2 + 1];
    sprintf(ab, "%d%d", *(int*)a, *(int*)b);
    sprintf(ba, "%d%d", *(int*)b, *(int*)a);
    return strcmp(ba, ab);
}

int main() {
    int n, numbers[MAX_N];
    
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &numbers[i]);
    }
    
    qsort(numbers, n, sizeof(int), compare);
    
    for (int i = 0; i < n; i++) {
        printf("%d", numbers[i]);
    }
    printf("\n");
    
    return 0;
}