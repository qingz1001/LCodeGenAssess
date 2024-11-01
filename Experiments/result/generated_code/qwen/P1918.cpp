#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, Q;
    scanf("%d", &n);
    int *a = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    scanf("%d", &Q);
    while (Q--) {
        int m;
        scanf("%d", &m);
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] == m) {
                printf("%d\n", i + 1);
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("0\n");
        }
    }
    free(a);
    return 0;
}