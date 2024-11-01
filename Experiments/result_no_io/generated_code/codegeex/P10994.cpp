#include <stdio.h>
#include <string.h>

int main() {
    int a, b;
    char s[100005];
    int studentSeats = 0, teacherSeats = 0;
    
    // 读取学生和老师人数
    scanf("%d %d", &a, &b);
    // 读取座位类型字符串
    scanf("%s", s);
    
    int n = strlen(s);
    
    // 统计学生座位和教师座位数量
    for (int i = 0; i < n; i++) {
        if (s[i] == 'S') {
            studentSeats++;
        } else {
            teacherSeats++;
        }
    }
    
    // 如果学生座位数量大于等于学生人数且教师座位数量大于等于教师人数
    if (studentSeats >= a && teacherSeats >= b) {
        printf("0\n");
    }
    // 如果学生座位数量小于学生人数且教师座位数量小于教师人数
    else if (studentSeats < a && teacherSeats < b) {
        printf("-1\n");
    }
    // 如果学生座位数量小于学生人数
    else if (studentSeats < a) {
        // 计算最少需要调整的座位数
        printf("%d\n", a - studentSeats);
    }
    // 如果教师座位数量小于教师人数
    else {
        // 计算最少需要调整的座位数
        printf("%d\n", b - teacherSeats);
    }
    
    return 0;
}