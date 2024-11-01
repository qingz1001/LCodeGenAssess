#include <stdio.h>

#define MAX_N 100000

int main() {
    int n;
    int bottles[MAX_N];
    int start = -1, end = -1;
    int max_interval = 0;

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &bottles[i]);
    }

    for (int i = 0; i < n; i++) {
        if (bottles[i] == 1) {
            if (start == -1) {
                start = i;
            }
            end = i;
        }
    }

    if (start == -1) {
        printf("0\n");
        return 0;
    }

    for (int i = start; i <= end; i++) {
        if (bottles[i] == 0) {
            int j = i;
            while (j <= end && bottles[j] == 0) {
                j++;
            }
            if (j - i > max_interval) {
                max_interval = j - i;
            }
            i = j - 1;
        }
    }

    printf("%d\n", end - start + 1 - max_interval);

    return 0;
}