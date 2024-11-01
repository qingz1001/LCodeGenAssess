#include <stdio.h>
#include <stdlib.h>

#define MAX_STUDENTS 20001
#define MAX_CLASSROOMS 20001

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int m, n;
        scanf("%d %d", &m, &n);

        int classroom[MAX_CLASSROOMS][MAX_STUDENTS];
        int classroom_size[MAX_CLASSROOMS];
        for (int i = 0; i < m; i++) {
            int k;
            scanf("%d", &k);
            classroom_size[i] = k;
            for (int j = 0; j < k; j++) {
                scanf("%d", &classroom[i][j]);
            }
        }

        int student_assigned[MAX_STUDENTS] = {0};

        int is_possible = 1;
        for (int i = 0; i < m; i++) {
            int assigned = 0;
            for (int j = 0; j < classroom_size[i]; j++) {
                if (student_assigned[classroom[i][j]] == 0) {
                    student_assigned[classroom[i][j]] = 1;
                    assigned = 1;
                    break;
                }
            }
            if (assigned == 0) {
                is_possible = 0;
                break;
            }
        }

        if (is_possible) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    return 0;
}