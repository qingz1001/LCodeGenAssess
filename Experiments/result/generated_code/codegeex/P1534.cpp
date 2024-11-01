#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int unhappy = 0;
    for (int i = 0; i < n; i++) {
        int school, extra;
        scanf("%d %d", &school, &extra);

        int total_time = school + extra;
        if (total_time > 8) {
            unhappy += total_time - 8;
        }
    }

    printf("%d\n", unhappy);
    return 0;
}