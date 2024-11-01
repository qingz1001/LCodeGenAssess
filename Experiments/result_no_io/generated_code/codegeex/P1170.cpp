#include <stdio.h>

int main() {
    int n, ax, ay, bx, by;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &ax, &ay);
        scanf("%d %d", &bx, &by);
        
        // 判断是否在同一行或同一列
        if (ax == bx || ay == by) {
            printf("no\n");
        } else {
            // 计算横纵坐标的差值
            int dx = ax - bx;
            int dy = ay - by;
            
            // 计算最大公约数
            int gcd = dx;
            int temp = dy;
            while (temp != 0) {
                int t = temp;
                temp = gcd % temp;
                gcd = t;
            }
            
            // 判断是否存在整数解
            if ((ax - bx) % gcd == 0 && (ay - by) % gcd == 0) {
                printf("no\n");
            } else {
                printf("yes\n");
            }
        }
    }
    return 0;
}