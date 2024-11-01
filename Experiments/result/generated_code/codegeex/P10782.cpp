#include <stdio.h>

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        long long a, c;
        scanf("%lld %lld", &a, &c);

        // Initialize the answer as -1 (default case when no valid b is found)
        long long b = -1;

        // Iterate over possible values of n from 1 to a
        for (long long n = 1; n <= a; ++n) {
            // Calculate b as the floor division of a by n
            long long temp_b = a / n;

            // Calculate c as the floor division of temp_b by m
            long long temp_c = temp_b / c;

            // If temp_c equals c, then we found a valid b
            if (temp_c == c) {
                b = temp_b;
                break;
            }
        }

        // Output the result for this test case
        printf("%lld\n", b);
    }

    return 0;
}