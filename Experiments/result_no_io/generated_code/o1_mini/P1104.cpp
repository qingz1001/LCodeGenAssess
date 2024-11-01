#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char name[21];
    int y, m, d;
    int index;
} Student;

int compare(const void *a, const void *b) {
    Student *s1 = (Student *)a;
    Student *s2 = (Student *)b;
    if (s1->y != s2->y)
        return s2->y - s1->y;
    if (s1->m != s2->m)
        return s2->m - s1->m;
    if (s1->d != s2->d)
        return s2->d - s1->d;
    return s2->index - s1->index;
}

int main(){
    int n;
    scanf("%d", &n);
    Student students[n];
    for(int i=0;i<n;i++){
        scanf("%s %d %d %d", students[i].name, &students[i].y, &students[i].m, &students[i].d);
        students[i].index = i;
    }
    qsort(students, n, sizeof(Student), compare);
    for(int i=0;i<n;i++)
        printf("%s\n", students[i].name);
    return 0;
}