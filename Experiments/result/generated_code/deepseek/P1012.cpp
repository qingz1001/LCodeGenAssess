#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    char str1[20], str2[20];
    sprintf(str1, "%s%s", (char *)a, (char *)b);
    sprintf(str2, "%s%s", (char *)b, (char *)a);
    return strcmp(str2, str1);
}

int main() {
    int n;
    scanf("%d", &n);
    char nums[20][10];
    
    for (int i = 0; i < n; i++) {
        scanf("%s", nums[i]);
    }
    
    qsort(nums, n, sizeof(nums[0]), compare);
    
    for (int i = 0; i < n; i++) {
        printf("%s", nums[i]);
    }
    printf("\n");
    
    return 0;
}