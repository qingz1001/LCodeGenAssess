#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 20
#define MAX_LEN 20

char numbers[MAX_N][MAX_LEN];

int compare(const void* a, const void* b) {
    char s1[MAX_LEN], s2[MAX_LEN];
    strcpy(s1, *(char**)a);
    strcpy(s2, *(char**)b);
    char temp1[MAX_LEN * 2], temp2[MAX_LEN * 2];
    strcpy(temp1, s1);
    strcat(temp1, s2);
    strcpy(temp2, s2);
    strcat(temp2, s1);
    return strcmp(temp2, temp1);
}

int main(){
    int n;
    scanf("%d", &n);
    char* arr[MAX_N];
    for(int i=0;i<n;i++){
        scanf("%s", numbers[i]);
        arr[i] = numbers[i];
    }
    qsort(arr, n, sizeof(char*), compare);
    for(int i=0;i<n;i++) printf("%s", arr[i]);
    return 0;
}