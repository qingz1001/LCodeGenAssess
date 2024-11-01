#include <stdio.h>

#define MAX_N 1001

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    int nums[MAX_N] = {0};
    int count = 0;

    for (int i = 2; i <= n; i++) {
        if (nums[i] == 0) {
            for (int j = i; j <= n; j += i) {
                if (nums[j] == 0) {
                    nums[j] = 1;
                    count++;
                    if (count == k) {
                        printf("%d\n", j);
                        return 0;
                    }
                }
            }
        }
    }

    return 0;
}