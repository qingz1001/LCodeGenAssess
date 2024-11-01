#include <stdio.h>
#include <stdlib.h>

int main() {
    int s1, s2, s3;
    scanf("%d %d %d", &s1, &s2, &s3);

    int max_sum = s1 + s2 + s3;
    int min_sum = 3;
    int *counts = (int *)calloc(max_sum - min_sum + 1, sizeof(int));

    for (int i = 1; i <= s1; i++) {
        for (int j = 1; j <= s2; j++) {
            for (int k = 1; k <= s3; k++) {
                counts[i + j + k - min_sum]++;
            }
        }
    }

    int max_count = 0;
    int result = max_sum;

    for (int sum = min_sum; sum <= max_sum; sum++) {
        if (counts[sum - min_sum] > max_count) {
            max_count = counts[sum - min_sum];
            result = sum;
        } else if (counts[sum - min_sum] == max_count && sum < result) {
            result = sum;
        }
    }

    printf("%d\n", result);
    free(counts);
    return 0;
}