#include <stdio.h>
#include <stdlib.h>

struct Student {
    int id;
    int chinese;
    int math;
    int english;
    int total;
};

int compare(const void *a, const void *b) {
    struct Student *sa = (struct Student *)a;
    struct Student *sb = (struct Student *)b;
    
    if (sa->total != sb->total)
        return sb->total - sa->total;
    if (sa->chinese != sb->chinese)
        return sb->chinese - sa->chinese;
    return sa->id - sb->id;
}

int main() {
    int n;
    scanf("%d", &n);
    
    struct Student students[300];
    
    for (int i = 0; i < n; i++) {
        students[i].id = i + 1;
        scanf("%d %d %d", &students[i].chinese, &students[i].math, &students[i].english);
        students[i].total = students[i].chinese + students[i].math + students[i].english;
    }
    
    qsort(students, n, sizeof(struct Student), compare);
    
    for (int i = 0; i < 5 && i < n; i++) {
        printf("%d %d\n", students[i].id, students[i].total);
    }
    
    return 0;
}