#include <stdio.h>
#include <stdlib.h>

#define MAX_STUDENTS 20001

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int m, n;
        scanf("%d %d", &m, &n);

        int *students_in_classroom = (int *)calloc(m + 1, sizeof(int));
        int *classroom_for_student = (int *)calloc(n + 1, sizeof(int));

        for (int i = 0; i < m; i++) {
            int k;
            scanf("%d", &k);
            for (int j = 0; j < k; j++) {
                int student;
                scanf("%d", &student);
                classroom_for_student[student] = i + 1;
            }
        }

        int has_empty_classroom = 0;
        for (int i = 1; i <= n; i++) {
            if (classroom_for_student[i] == 0) {
                has_empty_classroom = 1;
                break;
            }
            students_in_classroom[classroom_for_student[i]]++;
        }

        if (has_empty_classroom) {
            printf("NO\n");
        } else {
            int all_students_assigned = 1;
            for (int i = 1; i <= m; i++) {
                if (students_in_classroom[i] == 0) {
                    all_students_assigned = 0;
                    break;
                }
            }
            if (all_students_assigned) {
                printf("YES\n");
            } else {
                printf("NO\n");
            }
        }

        free(students_in_classroom);
        free(classroom_for_student);
    }

    return 0;
}