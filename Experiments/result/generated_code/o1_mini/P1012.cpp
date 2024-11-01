#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 20
#define MAX_LEN 12

char numbers[MAX_N][MAX_LEN];

int cmp(const void *a, const void *b) {
    const char *s1 = *(const char **)a;
    const char *s2 = *(const char **)b;
    char combined1[MAX_LEN * 2];
    char combined2[MAX_LEN * 2];
    
    strcpy(combined1, s1);
    strcat(combined1, s2);
    
    strcpy(combined2, s2);
    strcat(combined2, s1);
    
    return strcmp(combined2, combined1);
}

int main(){
    int n;
    scanf("%d", &n);
    char *arr[MAX_N];
    for(int i=0;i<n;i++){
        scanf("%s", numbers[i]);
        arr[i] = numbers[i];
    }
    qsort(arr, n, sizeof(char*), cmp);
    for(int i=0;i<n;i++) {
        printf("%s", arr[i]);
    }
    printf("\n");
    return 0;
}