#include <stdio.h>

int main() {
    int n, k;
    while (scanf("%d %d", &n, &k) != EOF) {
        long long total_smokes = n;
        long long remaining_tips = n;

        while (remaining_tips >= k) {
            total_smokes += remaining_tips / k;
            remaining_tips = remaining_tips / k + remaining_tips % k;
        }

        printf("%lld\n", total_smokes);
    }
    return 0;
}