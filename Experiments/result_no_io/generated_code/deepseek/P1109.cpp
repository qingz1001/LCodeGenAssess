#include <stdio.h>
#include <stdlib.h>

int min_moves(int n, int *students, int L, int R) {
    int total_students = 0;
    for (int i = 0; i < n; i++) {
        total_students += students[i];
    }

    if (total_students < n * L || total_students > n * R) {
        return -1;
    }

    int moves = 0;
    int surplus = 0, deficit = 0;

    for (int i = 0; i < n; i++) {
        if (students[i] > R) {
            surplus += students[i] - R;
        } else if (students[i] < L) {
            deficit += L - students[i];
        }
    }

    return surplus > deficit ? surplus : deficit;
}

int main() {
    int n;
    scanf("%d", &n);

    int *students = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &students[i]);
    }

    int L, R;
    scanf("%d %d", &L, &R);

    int result = min_moves(n, students, L, R);
    printf("%d\n", result);

    free(students);
    return 0;
}