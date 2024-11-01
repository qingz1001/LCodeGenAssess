#include <stdio.h>
#include <string.h>

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    char s[100001];
    scanf("%s", s);

    int n = strlen(s);
    int student_seats = 0, teacher_seats = 0;

    for (int i = 0; i < n; i++) {
        if (s[i] == 'S') {
            student_seats++;
        } else if (s[i] == 'T') {
            teacher_seats++;
        }
    }

    if (student_seats < a) {
        int needed_student_seats = a - student_seats;
        if (teacher_seats < needed_student_seats) {
            printf("-1\n");
            return 0;
        } else {
            printf("%d\n", needed_student_seats);
            return 0;
        }
    } else if (teacher_seats < b) {
        int needed_teacher_seats = b - teacher_seats;
        if (student_seats < needed_teacher_seats) {
            printf("-1\n");
            return 0;
        } else {
            printf("%d\n", needed_teacher_seats);
            return 0;
        }
    } else {
        printf("0\n");
        return 0;
    }
}