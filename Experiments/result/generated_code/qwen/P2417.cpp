#include <stdio.h>
#include <stdlib.h>

#define MAX_STUDENTS 20005
#define MAX_CLASSROOMS 20005

int main() {
    int T;
    scanf("%d", &T);
    
    while (T--) {
        int m, n;
        scanf("%d %d", &m, &n);
        
        int students[MAX_STUDENTS] = {0};
        
        for (int i = 0; i < m; i++) {
            int k;
            scanf("%d", &k);
            for (int j = 0; j < k; j++) {
                int student;
                scanf("%d", &student);
                students[student]++;
            }
        }
        
        int has_student = 0;
        for (int i = 1; i <= n; i++) {
            if (students[i] > 0) {
                has_student = 1;
                break;
            }
        }
        
        if (has_student) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    
    return 0;
}