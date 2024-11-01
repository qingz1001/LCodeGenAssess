#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int Chinese;
    int Math;
    int English;
    int total;
} Student;

int cmp(const void *a, const void *b){
    Student s1 = *(Student*)a;
    Student s2 = *(Student*)b;
    if(s1.total != s2.total){
        return s2.total - s1.total;
    }
    if(s1.Chinese != s2.Chinese){
        return s2.Chinese - s1.Chinese;
    }
    return s1.id - s2.id;
}

int main(){
    int n;
    scanf("%d", &n);
    Student students[300];
    for(int i=0;i<n;i++){
        scanf("%d %d %d", &students[i].Chinese, &students[i].Math, &students[i].English);
        students[i].id = i+1;
        students[i].total = students[i].Chinese + students[i].Math + students[i].English;
    }
    qsort(students, n, sizeof(Student), cmp);
    int output = n < 5 ? n : 5;
    for(int i=0;i<output;i++){
        printf("%d %d\n", students[i].id, students[i].total);
    }
    return 0;
}