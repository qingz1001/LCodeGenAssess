#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int chinese;
    int math;
    int english;
    int total;
} Student;

int cmp(const void *a, const void *b) {
    Student *sa = (Student *)a;
    Student *sb = (Student *)b;
    if (sb->total != sa->total)
        return sb->total - sa->total;
    if (sb->chinese != sa->chinese)
        return sb->chinese - sa->chinese;
    return sa->id - sb->id;
}

int main(){
    int n;
    scanf("%d", &n);
    Student s[300];
    for(int i=1;i<=n;i++){
        scanf("%d %d %d", &s[i-1].chinese, &s[i-1].math, &s[i-1].english);
        s[i-1].id = i;
        s[i-1].total = s[i-1].chinese + s[i-1].math + s[i-1].english;
    }
    qsort(s, n, sizeof(Student), cmp);
    int limit = n < 5 ? n : 5;
    for(int i=0;i<limit;i++){
        printf("%d %d\n", s[i].id, s[i].total);
    }
    return 0;
}