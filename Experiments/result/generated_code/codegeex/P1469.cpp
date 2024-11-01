#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);

    int *sticks = (int *)malloc(n * sizeof(int));
    if (sticks == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    int i;
    for (i = 0; i < n; i++) {
        scanf("%d", &sticks[i]);
    }

    int oddStickLength = 0;
    for (i = 0; i < n; i++) {
        if (oddStickLength == 0) {
            oddStickLength = sticks[i];
        } else if (oddStickLength != sticks[i]) {
            printf("%d\n", oddStickLength);
            free(sticks);
            return 0;
        }
    }

    // If no odd stick length found, it means all sticks are the same length
    printf("%d\n", oddStickLength);
    free(sticks);
    return 0;
}