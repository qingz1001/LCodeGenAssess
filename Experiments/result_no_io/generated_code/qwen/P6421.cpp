#include <stdio.h>
#include <stdbool.h>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    bool isDeleted[1001];
    for (int i = 2; i <= n; i++) {
        isDeleted[i] = false;
    }

    int count = 0;
    for (int p = 2; p <= n; p++) {
        if (!isDeleted[p]) {
            count++;
            if (count == k) {
                printf("%d\n", p);
                return 0;
            }
            for (int multiple = p * 2; multiple <= n; multiple += p) {
                isDeleted[multiple] = true;
            }
        }
    }

    return 0;
}