#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char s[21];
    int y, m, d;
    int index;
} Student;

int cmp(const void *a, const void *b){
    Student *s1 = (Student *)a;
    Student *s2 = (Student *)b;
    if (s1->y != s2->y){
        return s1->y - s2->y;
    }
    if (s1->m != s2->m){
        return s1->m - s2->m;
    }
    if (s1->d != s2->d){
        return s1->d - s2->d;
    }
    return s2->index - s1->index;
}

int main(){
    int n;
    scanf("%d", &n);
    Student stu[n];
    for(int i=0;i<n;i++){
        scanf("%s %d %d %d", stu[i].s, &stu[i].y, &stu[i].m, &stu[i].d);
        stu[i].index = i;
    }
    qsort(stu, n, sizeof(Student), cmp);
    for(int i=0;i<n;i++) printf("%s\n", stu[i].s);
    return 0;
}