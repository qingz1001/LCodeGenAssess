#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 100005

int main() {
    int a, b;
    char s[MAX_N];
    scanf("%d %d", &a, &b);
    scanf("%s", s);

    int n = strlen(s);
    int student_seats = 0, teacher_seats = 0;

    for (int i = 0; i < n; i++) {
        if (s[i] == 'S') student_seats++;
        else teacher_seats++;
    }

    int needed_student_seats = a - student_seats;
    int needed_teacher_seats = b - teacher_seats;

    if (needed_student_seats + needed_teacher_seats > 0) {
        printf("-1\n");
    } else {
        int changes = 0;
        if (needed_student_seats > 0) {
            changes = needed_student_seats;
        } else if (needed_teacher_seats > 0) {
            changes = needed_teacher_seats;
        }
        printf("%d\n", changes);
    }

    return 0;
}