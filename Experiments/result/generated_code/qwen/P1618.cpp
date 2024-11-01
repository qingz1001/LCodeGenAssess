#include <stdio.h>
#include <stdlib.h>

#define MAX_NUMS 9
#define MAX_GROUPS 3

void find_triplets(int A, int B, int C) {
    int nums[MAX_NUMS] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int target_sum = (A + B + C);
    int group_sums[MAX_GROUPS];
    int used[MAX_NUMS];

    for (int i = 0; i < MAX_NUMS; i++) {
        used[i] = 0;
    }

    for (int a = 0; a < MAX_NUMS - 2; a++) {
        if (used[a]) continue;
        used[a] = 1;

        for (int b = a + 1; b < MAX_NUMS - 1; b++) {
            if (used[b]) continue;
            used[b] = 1;

            for (int c = b + 1; c < MAX_NUMS; c++) {
                if (used[c]) continue;
                used[c] = 1;

                int num1 = nums[a] * 100 + nums[b] * 10 + nums[c];
                int remaining_sum = target_sum - num1;
                int remaining_nums[MAX_NUMS - 3];
                int remaining_count = 0;

                for (int i = 0; i < MAX_NUMS; i++) {
                    if (!used[i]) {
                        remaining_nums[remaining_count++] = nums[i];
                    }
                }

                for (int d = 0; d < remaining_count - 1; d++) {
                    for (int e = d + 1; e < remaining_count; e++) {
                        int num2 = remaining_nums[d] * 100 + remaining_nums[e] * 10 + remaining_nums[e + 1];
                        int num3 = remaining_nums[e + 1] * 100 + remaining_nums[d] * 10 + remaining_nums[e];

                        if ((num2 + num3 == remaining_sum) && (num1 / num2 == A / B) && (num1 / num3 == A / C)) {
                            printf("%d %d %d\n", num1, num2, num3);
                        }
                    }
                }

                used[c] = 0;
            }

            used[b] = 0;
        }

        used[a] = 0;
    }
}

int main() {
    int A, B, C;
    scanf("%d %d %d", &A, &B, &C);
    find_triplets(A, B, C);
    return 0;
}