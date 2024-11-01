#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int bottles[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &bottles[i]);
    }

    int count = 0;
    int i = 0;
    while (i < n) {
        if (bottles[i] == 1) {
            count++;
            while (i < n && bottles[i] == 1) {
                i++;
            }
        } else {
            i++;
        }
    }

    printf("%d\n", count);
    return 0;
}