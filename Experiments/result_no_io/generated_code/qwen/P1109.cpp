#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, L, R;
    scanf("%d", &n);
    int *students = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &students[i]);
    }
    scanf("%d %d", &L, &R);

    int below_L = 0, above_R = 0;
    for (int i = 0; i < n; i++) {
        if (students[i] < L) {
            below_L += L - students[i];
        } else if (students[i] > R) {
            above_R += students[i] - R;
        }
    }

    if (below_L != above_R) {
        printf("-1\n");
    } else {
        printf("%d\n", below_L);
    }

    free(students);
    return 0;
}