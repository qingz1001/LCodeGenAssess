#include <stdio.h>
#include <string.h>

#define MAX_SUM 81

int main() {
    int s1, s2, s3;
    int count[MAX_SUM] = {0};
    int max_count = 0, result = 0;

    scanf("%d %d %d", &s1, &s2, &s3);

    for (int i = 1; i <= s1; i++) {
        for (int j = 1; j <= s2; j++) {
            for (int k = 1; k <= s3; k++) {
                int sum = i + j + k;
                count[sum]++;
                if (count[sum] > max_count) {
                    max_count = count[sum];
                    result = sum;
                } else if (count[sum] == max_count && sum < result) {
                    result = sum;
                }
            }
        }
    }

    printf("%d\n", result);

    return 0;
}