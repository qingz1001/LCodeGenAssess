#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    int total_seats = n;
    int total_people = a + b;

    if (total_people > total_seats) {
        printf("-1\n");
        return 0;
    }

    int student_diff = a - student_seats;
    int teacher_diff = b - teacher_seats;

    if (student_diff > 0 && teacher_diff > 0) {
        printf("-1\n");
        return 0;
    }

    if (student_diff <= 0 && teacher_diff <= 0) {
        printf("0\n");
        return 0;
    }

    printf("%d\n", abs(student_diff));

    return 0;
}