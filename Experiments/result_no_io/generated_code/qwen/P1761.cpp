#include <stdio.h>
#include <stdlib.h>

#define MAX_N 50
#define MAX_SIZE 30

int main() {
    int n;
    while (scanf("%d", &n) != EOF && n != 0) {
        int sizes[MAX_N];
        for (int i = 0; i < n; i++) {
            scanf("%d", &sizes[i]);
        }

        int x = 0;
        int visible[MAX_N] = {0};
        int count = 0;

        for (int i = 0; i < n; i++) {
            if (x + sizes[i] <= MAX_SIZE * 2) {
                visible[count++] = i + 1;
                x += sizes[i];
            }
        }

        for (int i = 0; i < count - 1; i++) {
            printf("%d ", visible[i]);
        }
        if (count > 0) {
            printf("%d\n", visible[count - 1]);
        } else {
            printf("\n");
        }
    }
    return 0;
}