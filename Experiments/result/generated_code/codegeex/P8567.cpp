#include <stdio.h>

// Function to calculate f(x) as described in the problem statement
int f(int x) {
    int ans = 0;
    while (x % 2 == 0) {
        x /= 2;
        ans += 1;
    }
    return ans;
}

int main() {
    int T;
    scanf("%d", &T); // Read the number of test cases
    while (T--) {
        long long l, r;
        scanf("%lld %lld", &l, &r); // Read the interval [l, r] for each test case

        // Calculate the number of integers i in [l, r] such that f(i) < f(i+1)
        // This is equivalent to counting the number of even numbers in the interval
        // because for even numbers, f(i) = 0 and for odd numbers, f(i+1) = 0
        // Thus, the answer is (r - l + 1) / 2
        long long result = (r - l + 1) / 2;
        printf("%lld\n", result);
    }
    return 0;
}