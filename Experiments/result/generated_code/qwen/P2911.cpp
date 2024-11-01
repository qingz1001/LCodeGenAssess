#include <stdio.h>
#include <stdlib.h>

#define MAX_SUM 60 // 最大可能的和为40+40+40=120，但我们需要一个更大的数组来存储计数

int main() {
    int s1, s2, s3;
    scanf("%d %d %d", &s1, &s2, &s3);

    int count[MAX_SUM + 1] = {0}; // 初始化计数数组为0
    int max_count = 0;
    int result_sum = 0;

    for (int i = 1; i <= s1; i++) {
        for (int j = 1; j <= s2; j++) {
            for (int k = 1; k <= s3; k++) {
                int sum = i + j + k;
                count[sum]++;
                if (count[sum] > max_count || (count[sum] == max_count && sum < result_sum)) {
                    max_count = count[sum];
                    result_sum = sum;
                }
            }
        }
    }

    printf("%d\n", result_sum);
    return 0;
}