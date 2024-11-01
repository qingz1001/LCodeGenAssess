#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);
    
    while (N--) {
        int A;
        scanf("%d", &A);
        
        // 计算位置A在第几个数字中
        int digit = 1;
        int count = 1;
        while (count < A) {
            digit++;
            count += digit;
        }
        
        // 计算位置A在该数字中的偏移量
        int offset = A - (count - digit);
        
        // 判断位置A上的数字是0还是1
        if (digit % 2 == 1) {
            // 奇数长度的数字
            if (offset % 3 == 1) {
                printf("1\n");
            } else {
                printf("0\n");
            }
        } else {
            // 偶数长度的数字
            if (offset % 3 == 1) {
                printf("0\n");
            } else {
                printf("1\n");
            }
        }
    }
    
    return 0;
}