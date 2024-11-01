#include <stdio.h>
#include <stdlib.h>

#define MAX_N 20005
#define MAX_M 20005

int main() {
    int T, m, n;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d", &m, &n);
        int *classrooms = (int *)malloc(m * sizeof(int));
        for (int i = 0; i < m; i++) {
            scanf("%d", &classrooms[i]);
        }
        int total_students = 0;
        for (int i = 0; i < m; i++) {
            total_students += classrooms[i];
        }
        if (total_students >= n) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
        free(classrooms);
    }
    return 0;
}