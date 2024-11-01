#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    
    int *students = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &students[i]);
    }
    
    int count = 1; // 至少需要一个宿舍
    int yyy_count = 0, c01_count = 0;
    
    for (int i = 0; i < N; i++) {
        if (students[i] == 1) {
            yyy_count++;
        } else {
            c01_count++;
        }
        
        if (abs(yyy_count - c01_count) > M) {
            count++;
            yyy_count = (students[i] == 1) ? 1 : 0;
            c01_count = (students[i] == 2) ? 1 : 0;
        }
    }
    
    printf("%d\n", count);
    
    free(students);
    return 0;
}