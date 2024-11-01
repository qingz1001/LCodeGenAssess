#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int chinese;
    int math;
    int english;
    int total;
} Student;

int compare(const void *a, const void *b) {
    Student *s1 = (Student *)a;
    Student *s2 = (Student *)b;
    
    if (s1->total != s2->total)
        return s2->total - s1->total;
    if (s1->chinese != s2->chinese)
        return s2->chinese - s1->chinese;
    return s1->id - s2->id;
}

int main() {
    int n;
    scanf("%d", &n);
    
    Student students[300];
    
    for (int i = 0; i < n; i++) {
        students[i].id = i + 1;
        scanf("%d %d %d", &students[i].chinese, &students[i].math, &students[i].english);
        students[i].total = students[i].chinese + students[i].math + students[i].english;
    }
    
    qsort(students, n, sizeof(Student), compare);
    
    for (int i = 0; i < 5 && i < n; i++) {
        printf("%d %d\n", students[i].id, students[i].total);
    }
    
    return 0;
}