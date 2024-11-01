#include <stdio.h>

int main() {
    int L, R;
    int count = 0;
    
    // 读取输入的两个整数 L 和 R
    scanf("%d %d", &L, &R);
    
    // 遍历 L 到 R 的所有整数
    for (int i = L; i <= R; i++) {
        int num = i;
        
        // 对每个数字进行逐位检查
        while (num > 0) {
            if (num % 10 == 2) {
                count++;
            }
            num /= 10;
        }
    }
    
    // 输出数字 2 出现的总次数
    printf("%d\n", count);
    
    return 0;
}