#include <stdio.h>

int main() {
    int s1, s2, s3;
    scanf("%d %d %d", &s1, &s2, &s3);

    int max_sum = s1 + s2 + s3;
    int frequency[max_sum + 1];
    for (int i = 0; i <= max_sum; i++) {
        frequency[i] = 0;
    }

    for (int i = 1; i <= s1; i++) {
        for (int j = 1; j <= s2; j++) {
            for (int k = 1; k <= s3; k++) {
                frequency[i + j + k]++;
            }
        }
    }

    int max_frequency = 0;
    int result_sum = 0;
    for (int i = 3; i <= max_sum; i++) {
        if (frequency[i] > max_frequency) {
            max_frequency = frequency[i];
            result_sum = i;
        }
    }

    printf("%d\n", result_sum);
    return 0;
}