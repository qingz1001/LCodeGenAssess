#include <stdio.h>
#include <stdlib.h>

#define MAX_STUDENTS 200001
#define MAX_OPERATIONS 5000

typedef struct {
    int id;
    int score;
} Student;

int compare(const void *a, const void *b) {
    return ((Student *)b)->score - ((Student *)a)->score;
}

void query(Student students[], int n, int a, int b) {
    Student range[MAX_STUDENTS];
    for (int i = a - 1; i <= b - 1; i++) {
        range[i] = students[i];
    }
    qsort(range, b - a + 1, sizeof(Student), compare);
    printf("%d\n", range[0].score);
}

void update(Student students[], int n, int a, int b) {
    if (students[a - 1].score < b) {
        students[a - 1].score = b;
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    Student students[n];
    for (int i = 0; i < n; i++) {
        students[i].id = i + 1;
        scanf("%d", &students[i].score);
    }

    char c;
    int a, b;
    for (int i = 0; i < m; i++) {
        scanf(" %c %d %d", &c, &a, &b);
        if (c == 'Q') {
            query(students, n, a, b);
        } else if (c == 'U') {
            update(students, n, a, b);
        }
    }

    return 0;
}