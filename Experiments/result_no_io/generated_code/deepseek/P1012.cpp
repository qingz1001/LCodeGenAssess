#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    char s1[20], s2[20];
    sprintf(s1, "%s%s", (char *)a, (char *)b);
    sprintf(s2, "%s%s", (char *)b, (char *)a);
    return strcmp(s2, s1);
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