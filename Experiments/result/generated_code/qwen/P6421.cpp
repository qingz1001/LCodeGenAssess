#include <stdio.h>
#include <stdbool.h>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    bool *isDeleted = (bool *)calloc(n + 1, sizeof(bool));
    int count = 0;

    for (int i = 2; i <= n; i++) {
        if (!isDeleted[i]) {
            count++;
            if (count == k) {
                printf("%d\n", i);
                break;
            }
            for (int j = i * 2; j <= n; j += i) {
                isDeleted[j] = true;
            }
        }
    }

    free(isDeleted);
    return 0;
}