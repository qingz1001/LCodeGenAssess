#include <stdio.h>

int main() {
    int n, i;
    int a[7] = {0}; // 存储罗马数字字符出现的次数

    scanf("%d", &n);

    for (i = 1; i <= n; i++) {
        if (i >= 1000) a[0]++; // M
        if (i % 1000 >= 900) { // CM
            a[6]++;
            i++;
        }
        if (i % 1000 >= 500) { // D
            a[5]++;
            i -= 500;
        }
        if (i % 1000 >= 400) { // CD
            a[4]++;
            i -= 400;
        }
        if (i % 1000 >= 100) { // C
            a[3]++;
            i -= 100;
        }
        if (i % 100 >= 90) { // XC
            a[2]++;
            i -= 90;
        }
        if (i % 100 >= 50) { // L
            a[1]++;
            i -= 50;
        }
        if (i % 100 >= 40) { // XL
            a[0]++;
            i -= 40;
        }
        if (i % 100 >= 10) { // X
            a[0]++;
            i -= 10;
        }
        if (i >= 9) { // IX
            a[2]++;
            i -= 9;
        }
        if (i >= 5) { // V
            a[1]++;
            i -= 5;
        }
        if (i >= 4) { // IV
            a[0]++;
            i -= 4;
        }
        if (i >= 1) { // I
            a[0]++;
            i -= 1;
        }
    }

    for (i = 0; i < 7; i++) {
        if (a[i] > 0) {
            if (i == 0) printf("I %d\n", a[i]);
            if (i == 1) printf("V %d\n", a[i]);
            if (i == 2) printf("X %d\n", a[i]);
            if (i == 3) printf("L %d\n", a[i]);
            if (i == 4) printf("C %d\n", a[i]);
            if (i == 5) printf("D %d\n", a[i]);
            if (i == 6) printf("M %d\n", a[i]);
        }
    }

    return 0;
}