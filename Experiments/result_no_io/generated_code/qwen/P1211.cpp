#include <stdio.h>
#include <stdlib.h>

int count = 0;

void backtrack(int *nums, int used[], int pos, int target) {
    if (pos == 5) {
        if (target == 0) count++;
        return;
    }
    for (int i = 0; i < 9; i++) {
        if (!used[i]) {
            used[i] = 1;
            backtrack(nums, used, pos + 1, target - nums[i]);
            used[i] = 0;
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    int *nums = (int *)malloc(n * sizeof(int));
    int *used = (int *)calloc(9, sizeof(int));

    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
    }

    backtrack(nums, used, 0, 4884);

    printf("%d\n", count);

    free(nums);
    free(used);

    return 0;
}