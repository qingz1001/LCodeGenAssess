#include <stdio.h>
#include <stdlib.h>

// 定义学校结构体，包含预计分数线
typedef struct {
    int score;
} School;

// 定义学生结构体，包含估分
typedef struct {
    int score;
} Student;

// 比较函数，用于qsort排序
int compare(const void *a, const void *b) {
    return (*(School *)a).score - (*(School *)b).score;
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    School *schools = (School *)malloc(m * sizeof(School));
    Student *students = (Student *)malloc(n * sizeof(Student));

    for (int i = 0; i < m; i++) {
        scanf("%d", &schools[i].score);
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", &students[i].score);
    }

    // 对学校和学生的分数进行排序
    qsort(schools, m, sizeof(School), compare);

    int totalDiscontentment = 0;

    // 对每个学生的估分，找到最接近的学校分数线
    for (int i = 0; i < n; i++) {
        int minDiscontentment = abs(students[i].score - schools[0].score);
        int closestSchoolIndex = 0;

        for (int j = 1; j < m; j++) {
            int currentDiscontentment = abs(students[i].score - schools[j].score);
            if (currentDiscontentment < minDiscontentment) {
                minDiscontentment = currentDiscontentment;
                closestSchoolIndex = j;
            }
        }

        totalDiscontentment += minDiscontentment;
    }

    printf("%d\n", totalDiscontentment);

    free(schools);
    free(students);

    return 0;
}