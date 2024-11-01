#include <stdio.h>

int main() {
    int n, k;
    while (scanf("%d %d", &n, &k) != EOF) {
        int total = n;
        while (n >= k) {
            int new_smokes = n / k;
            total += new_smokes;
            n = n % k + new_smokes;
        }
        printf("%d\n", total);
    }
    return 0;
}