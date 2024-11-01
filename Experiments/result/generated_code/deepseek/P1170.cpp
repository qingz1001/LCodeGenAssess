#include <stdio.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int is_safe(int ax, int ay, int bx, int by) {
    if (ax == bx || ay == by) {
        return 0; // 猎人和兔八哥在同一行或同一列，不安全
    }
    if (gcd(abs(ax - bx), abs(ay - by)) == 1) {
        return 1; // 猎人和兔八哥的连线上没有其他树，安全
    }
    return 0; // 猎人和兔八哥的连线上有其他树，不安全
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int ax, ay, bx, by;
        scanf("%d %d %d %d", &ax, &ay, &bx, &by);
        if (is_safe(ax, ay, bx, by)) {
            printf("yes\n");
        } else {
            printf("no\n");
        }
    }
    return 0;
}