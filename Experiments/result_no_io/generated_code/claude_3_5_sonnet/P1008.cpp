#include <stdio.h>

int main() {
    int a, b, c;
    int used[10] = {0};
    
    for (a = 123; a <= 329; a++) {
        b = 2 * a;
        c = 3 * a;
        
        // 重置used数组
        for (int i = 0; i < 10; i++) {
            used[i] = 0;
        }
        
        // 检查每个数字是否出现且只出现一次
        if (check(a, used) && check(b, used) && check(c, used)) {
            printf("%d %d %d\n", a, b, c);
        }
    }
    
    return 0;
}

int check(int num, int used[]) {
    while (num > 0) {
        int digit = num % 10;
        if (digit == 0 || used[digit]) {
            return 0;
        }
        used[digit] = 1;
        num /= 10;
    }
    return 1;
}