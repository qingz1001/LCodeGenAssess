#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 比较函数，用于qsort
int compare(const void *a, const void *b) {
    char str1[20], str2[20];
    sprintf(str1, "%s%s", *(char**)a, *(char**)b);
    sprintf(str2, "%s%s", *(char**)b, *(char**)a);
    return strcmp(str2, str1);
}

int main() {
    int n;
    scanf("%d", &n);
    char **arr = (char**)malloc(n * sizeof(char*));
    
    for (int i = 0; i < n; i++) {
        arr[i] = (char*)malloc(20 * sizeof(char));
        scanf("%s", arr[i]);
    }
    
    qsort(arr, n, sizeof(char*), compare);
    
    for (int i = 0; i < n; i++) {
        printf("%s", arr[i]);
    }
    
    for (int i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);
    
    return 0;
}