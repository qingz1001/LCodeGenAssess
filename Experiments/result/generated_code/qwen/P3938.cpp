#include <stdio.h>

int main() {
    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        if (a > b) {
            int temp = a;
            a = b;
            b = temp;
        }
        while (b != 0) {
            int t = b;
            b = a % b;
            a = t;
        }
        printf("%d\n", a);
    }
    return 0;
}