#include <stdio.h>
#include <string.h>

#define MAXN 25
#define MAX_LEN 11

int compare(const void *a, const void *b) {
    char s1[MAX_LEN * 2], s2[MAX_LEN * 2];
    sprintf(s1, "%d%d", *(int *)b, *(int *)a);
    sprintf(s2, "%d%d", *(int *)a, *(int *)b);
    return strcmp(s1, s2);
}

int main() {
    int n;
    scanf("%d", &n);
    int nums[MAXN];
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
    }

    qsort(nums, n, sizeof(int), compare);

    if (nums[0] == 0) {
        printf("0\n");
        return 0;
    }

    for (int i = 0; i < n; i++) {
        printf("%d", nums[i]);
    }
    printf("\n");

    return 0;
}