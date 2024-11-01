#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int main() {
    int nums[8];
    for (int i = 0; i < 8; i++) {
        scanf("%d", &nums[i]);
    }

    qsort(nums, 8, sizeof(int), compare);

    int max_sum = 0;
    int indices[5];

    for (int i = 0; i < 5; i++) {
        max_sum += nums[i];
        indices[i] = i + 1;
    }

    printf("%d\n", max_sum);
    for (int i = 0; i < 5; i++) {
        printf("%d ", indices[i]);
    }
    printf("\n");

    return 0;
}