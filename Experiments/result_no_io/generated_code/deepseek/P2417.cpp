#include <stdio.h>
#include <stdbool.h>

#define MAX_N 20000
#define MAX_M 20000

int main() {
    int T;
    scanf("%d", &T);
    
    while (T--) {
        int m, n;
        scanf("%d %d", &m, &n);
        
        bool classroom_has_student[MAX_M] = {false};
        bool student_assigned[MAX_N] = {false};
        
        for (int i = 0; i < m; i++) {
            int k_i;
            scanf("%d", &k_i);
            for (int j = 0; j < k_i; j++) {
                int p_i_j;
                scanf("%d", &p_i_j);
                classroom_has_student[i] = true;
                student_assigned[p_i_j - 1] = true;
            }
        }
        
        bool all_classrooms_have_students = true;
        for (int i = 0; i < m; i++) {
            if (!classroom_has_student[i]) {
                all_classrooms_have_students = false;
                break;
            }
        }
        
        bool all_students_assigned = true;
        for (int i = 0; i < n; i++) {
            if (!student_assigned[i]) {
                all_students_assigned = false;
                break;
            }
        }
        
        if (all_classrooms_have_students && all_students_assigned) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    
    return 0;
}