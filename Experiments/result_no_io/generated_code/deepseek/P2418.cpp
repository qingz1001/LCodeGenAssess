#include <stdio.h>
#include <stdlib.h>

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    int *students = (int *)malloc((N + 1) * sizeof(int));
    for (int i = 1; i <= N; i++) {
        scanf("%d", &students[i]);
    }

    int count = 0;
    int i = 1;
    while (i <= N) {
        int yyy_count = 0, c01_count = 0;
        int j = i;
        while (j <= N) {
            if (students[j] == 1) yyy_count++;
            else c01_count++;
            if (abs(yyy_count - c01_count) > M) {
                break;
            }
            j++;
        }
        count++;
        i = j;
    }

    printf("%d\n", count);
    free(students);
    return 0;
}