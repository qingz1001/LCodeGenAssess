#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, *sums, *nums;
    while (scanf("%d", &n) != EOF) {
        sums = (int *)malloc((n * (n - 1)) / 2 * sizeof(int));
        nums = (int *)malloc(n * sizeof(int));

        for (int i = 0; i < (n * (n - 1)) / 2; i++) {
            scanf("%d", &sums[i]);
        }

        // Sort the sums array
        for (int i = 0; i < (n * (n - 1)) / 2 - 1; i++) {
            for (int j = 0; j < (n * (n - 1)) / 2 - i - 1; j++) {
                if (sums[j] > sums[j + 1]) {
                    int temp = sums[j];
                    sums[j] = sums[j + 1];
                    sums[j + 1] = temp;
                }
            }
        }

        // Check if it's possible to find such numbers
        int found = 0;
        for (int a = 0; a < n; a++) {
            for (int b = a + 1; b < n; b++) {
                for (int c = b + 1; c < n; c++) {
                    int count = 0;
                    for (int i = 0; i < (n * (n - 1)) / 2; i++) {
                        if ((a + b == sums[i]) || (a + c == sums[i]) || (b + c == sums[i])) {
                            count++;
                        }
                    }
                    if (count == (n * (n - 1)) / 2) {
                        nums[0] = a;
                        nums[1] = b;
                        nums[2] = c;
                        found = 1;
                        break;
                    }
                }
                if (found) break;
            }
            if (found) break;
        }

        if (found) {
            printf("%d %d %d\n", nums[0], nums[1], nums[2]);
        } else {
            printf("Impossible\n");
        }

        free(sums);
        free(nums);
    }
    return 0;
}