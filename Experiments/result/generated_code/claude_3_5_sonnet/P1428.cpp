#include <stdio.h>

#define MAX_N 100

int main() {
    int n, i, j;
    int fish[MAX_N];
    int count[MAX_N] = {0};

    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        scanf("%d", &fish[i]);
    }

    for (i = 0; i < n; i++) {
        for (j = i - 1; j >= 0; j--) {
            if (fish[j] < fish[i]) {
                count[i]++;
            }
        }
    }

    for (i = 0; i < n; i++) {
        printf("%d ", count[i]);
    }

    return 0;
}