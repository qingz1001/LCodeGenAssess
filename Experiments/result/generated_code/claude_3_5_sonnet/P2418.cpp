#include <stdio.h>
#include <stdlib.h>

#define MAX_N 500000

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    int* students = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &students[i]);
    }

    int count = 1;
    int yyy = 0, c01 = 0;
    int start = 0;

    for (int i = 0; i < N; i++) {
        if (students[i] == 1) yyy++;
        else c01++;

        if (yyy == 0 || c01 == 0) continue;

        if (abs(yyy - c01) > M) {
            count++;
            yyy = (students[i] == 1) ? 1 : 0;
            c01 = (students[i] == 2) ? 1 : 0;
            start = i;
        }
    }

    printf("%d\n", count);

    free(students);
    return 0;
}