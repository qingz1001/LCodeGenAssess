#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int bottles[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &bottles[i]);
    }

    int min_bottles = 0;
    int max_range = -1;

    for (int i = 0; i < n; i++) {
        if (bottles[i] == 1) {
            if (i > max_range) {
                min_bottles++;
                max_range = i;
            }
            max_range = i;
        }
    }

    printf("%d\n", min_bottles);
    return 0;
}