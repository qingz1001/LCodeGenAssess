#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int min_numbers = 3;
    int count = 0;

    // The minimal set of numbers is {1, 2, 4}
    // Generate all possible combinations of these numbers
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n - i; j++) {
            for (int k = 0; k <= n - i - j; k++) {
                int sum = i + j + k;
                if (sum <= n) {
                    count++;
                } else {
                    break;
                }
            }
        }
    }

    printf("%d %d\n", min_numbers, count);

    return 0;
}