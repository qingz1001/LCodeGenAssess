#include <stdio.h>

int main() {
    int nums[3];
    char order[4];
    
    // 读取三个整数
    for (int i = 0; i < 3; i++) {
        scanf("%d", &nums[i]);
    }
    
    // 读取顺序字符串
    scanf("%s", order);
    
    // 找到最小的数
    int A = nums[0], B = nums[1], C = nums[2];
    if (A > B) {
        int temp = A;
        A = B;
        B = temp;
    }
    if (B > C) {
        int temp = B;
        B = C;
        C = temp;
    }
    if (A > B) {
        int temp = A;
        A = B;
        B = temp;
    }
    
    // 按照给定的顺序输出
    for (int i = 0; i < 3; i++) {
        if (order[i] == 'A') {
            printf("%d", A);
        } else if (order[i] == 'B') {
            printf("%d", B);
        } else if (order[i] == 'C') {
            printf("%d", C);
        }
        if (i < 2) {
            printf(" ");
        }
    }
    
    return 0;
}