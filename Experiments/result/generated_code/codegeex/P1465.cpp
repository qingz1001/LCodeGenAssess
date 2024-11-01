#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int count[7] = {0}; // I V X L C D M

    for (int i = 1; i <= n; i++) {
        int temp = i;
        while (temp >= 1000) {
            count[6]++;
            temp -= 1000;
        }
        if (temp >= 900) {
            count[5]++;
            temp -= 900;
        }
        if (temp >= 500) {
            count[4]++;
            temp -= 500;
        }
        if (temp >= 400) {
            count[3]++;
            temp -= 400;
        }
        while (temp >= 100) {
            count[2]++;
            temp -= 100;
        }
        if (temp >= 90) {
            count[1]++;
            temp -= 90;
        }
        while (temp >= 50) {
            count[0]++;
            temp -= 50;
        }
        if (temp >= 40) {
            count[1]++;
            temp -= 40;
        }
        while (temp >= 10) {
            count[0]++;
            temp -= 10;
        }
        if (temp >= 9) {
            count[1]++;
            temp -= 9;
        }
        while (temp >= 5) {
            count[0]++;
            temp -= 5;
        }
        if (temp >= 4) {
            count[1]++;
            temp -= 4;
        }
        while (temp >= 1) {
            count[0]++;
            temp -= 1;
        }
    }

    printf("I %d\n", count[0]);
    printf("V %d\n", count[1]);
    printf("X %d\n", count[2]);
    printf("L %d\n", count[3]);
    printf("C %d\n", count[4]);
    printf("D %d\n", count[5]);
    printf("M %d\n", count[6]);

    return 0;
}