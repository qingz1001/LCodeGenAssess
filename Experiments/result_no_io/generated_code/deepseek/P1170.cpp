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
    int dx = ax - bx;
    int dy = ay - by;
    return gcd(abs(dx), abs(dy)) == 1;
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