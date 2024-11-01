#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000
#define MAX_C 5

typedef struct {
    int T;
    int B;
} Student;

int compare(const void *a, const void *b) {
    Student s1 = *(Student *)a;
    Student s2 = *(Student *)b;
    if (s1.B != s2.B) return s2.B - s1.B;
    return s1.T - s2.T;
}

int main() {
    int C, N;
    scanf("%d", &C);
    while (C--) {
        scanf("%d", &N);
        Student students[MAX_N];
        for (int i = 0; i < N; i++) {
            scanf("%d %d", &students[i].T, &students[i].B);
        }
        qsort(students, N, sizeof(Student), compare);
        long long time = 0;
        int last_or = 0;
        for (int i = 0; i < N; i++) {
            int or_val = last_or | students[i].T;
            int and_val = last_or & students[i].T;
            time += or_val - and_val;
            last_or = or_val;
        }
        printf("%lld\n", time);
    }
    return 0;
}