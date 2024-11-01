#include <stdio.h>
#include <string.h>

int main() {
    int s1, s2, s3;
    scanf("%d%d%d", &s1, &s2, &s3);

    int max_count = 0;
    int max_sum = 0;
    int freq[1001] = {0};

    // Calculate all possible sums and their frequencies
    for (int i = 1; i <= s1; i++) {
        for (int j = 1; j <= s2; j++) {
            for (int k = 1; k <= s3; k++) {
                int sum = i + j + k;
                freq[sum]++;
            }
        }
    }

    // Find the sum with the maximum frequency
    for (int i = 3; i <= s1 + s2 + s3; i++) {
        if (freq[i] > max_count) {
            max_count = freq[i];
            max_sum = i;
        }
    }

    printf("%d\n", max_sum);
    return 0;
}