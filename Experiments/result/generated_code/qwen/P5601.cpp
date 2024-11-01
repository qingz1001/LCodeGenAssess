#include <stdio.h>
#include <string.h>

#define MAX_N 100
#define MAX_Q 100
#define MAX_S 100

int main() {
    int n, q;
    char problem[MAX_N][MAX_S];
    char answer[MAX_N][MAX_S];
    char exam_problem[MAX_Q][MAX_S];
    char options[MAX_Q][4][MAX_S];
    char result[MAX_Q];

    scanf("%d %d", &n, &q);

    for (int i = 0; i < n; i++) {
        scanf("%s %s", problem[i], answer[i]);
    }

    for (int i = 0; i < q; i++) {
        scanf("%s %s %s %s %s", exam_problem[i], options[i][0], options[i][1], options[i][2], options[i][3]);
    }

    for (int i = 0; i < q; i++) {
        for (int j = 0; j < 4; j++) {
            if (strcmp(options[i][j], answer[find_problem_index(problem, exam_problem[i], n)]) == 0) {
                result[i] = 'A' + j;
                break;
            }
        }
    }

    for (int i = 0; i < q; i++) {
        printf("%c\n", result[i]);
    }

    return 0;
}

int find_problem_index(char problem[][MAX_S], char target[MAX_S], int n) {
    for (int i = 0; i < n; i++) {
        if (strcmp(problem[i], target) == 0) {
            return i;
        }
    }
    return -1; // This should never happen as per the problem statement
}