#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int bottles[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &bottles[i]);
    }

    int start = -1, end = -1;
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
    } else {
        printf("%d\n", end - start + 1);
    }

    return 0;
}