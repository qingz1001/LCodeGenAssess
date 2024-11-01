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

    int belowL = 0, aboveR = 0;
    for (int i = 0; i < n; i++) {
        if (students[i] < L) belowL += L - students[i];
        else if (students[i] > R) aboveR += students[i] - R;
    }

    if (belowL != aboveR) {
        printf("-1\n");
        free(students);
        return 0;
    }

    printf("%d\n", belowL);

    free(students);
    return 0;
}