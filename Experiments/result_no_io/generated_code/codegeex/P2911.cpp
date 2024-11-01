#include <stdio.h>

int main() {
    int s1, s2, s3;
    scanf("%d%d%d", &s1, &s2, &s3);

    int maxCount = 0;
    int mostFrequentSum = 0;

    // Iterate over all possible sums of the three dice
    for (int i = 1; i <= s1; i++) {
        for (int j = 1; j <= s2; j++) {
            for (int k = 1; k <= s3; k++) {
                int sum = i + j + k;
                int count = 0;

                // Count how many times this sum appears
                for (int x = 1; x <= s1; x++) {
                    for (int y = 1; y <= s2; y++) {
                        for (int z = 1; z <= s3; z++) {
                            if (x + y + z == sum) {
                                count++;
                            }
                        }
                    }
                }

                // Check if this sum is the most frequent so far
                if (count > maxCount || (count == maxCount && sum < mostFrequentSum)) {
                    maxCount = count;
                    mostFrequentSum = sum;
                }
            }
        }
    }

    printf("%d\n", mostFrequentSum);
    return 0;
}