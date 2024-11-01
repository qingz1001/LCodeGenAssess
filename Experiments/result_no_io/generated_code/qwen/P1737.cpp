#include <stdio.h>
#include <math.h>

int main() {
    int task;
    scanf("%d", &task);

    if (task == 1) {
        printf("I\n");
        printf("I\n");
        printf("+ 1 2\n");
        printf("* -1 1\n");
    } else if (task == 2) {
        printf("I\n");
        printf("C 1 17\n");
        printf("S 1\n");
        printf("C 1 -1\n");
        printf("1\n");
    } else if (task == 3) {
        printf("I\n");
        printf("C 1 0\n");
        printf("P 1 1\n");
        printf("O 1\n");
    } else if (task == 4) {
        printf("I\n");
        printf("C 1 0\n");
        printf("P 1 1\n");
        printf("O 1\n");
    } else if (task == 5) {
        for (int i = 1; i <= 32; ++i) {
            printf("I\n");
        }
        for (int i = 32; i >= 1; --i) {
            printf("< %d %d\n", i + 1, 33);
        }
        printf("O 33\n");
    } else if (task == 6) {
        printf("I\n");
        for (int i = 31; i >= 0; --i) {
            printf("> 1 %d\n", i);
        }
        printf("O 1\n");
    } else if (task == 7) {
        printf("I\n");
        printf("I\n");
        printf("^ 1 2\n");
        printf("O 1\n");
    } else if (task == 8) {
        printf("I\n");
        printf("C 1 1\n");
        printf("/ 1 10\n");
        printf("O 1\n");
    } else if (task == 9) {
        for (int i = 1; i <= 16; ++i) {
            printf("I\n");
        }
        for (int i = 1; i <= 15; ++i) {
            printf("C %d %d\n", i, i + 1);
        }
        printf("M 1 16\n");
        printf("O 1\n");
    } else if (task == 10) {
        printf("I\n");
        printf("I\n");
        printf("I\n");
        printf("C 1 0\n");
        printf("C 2 1\n");
        printf("C 3 2\n");
        printf("* 2 3\n");
        printf("/ 3 1\n");
        printf("O 3\n");
    }

    return 0;
}